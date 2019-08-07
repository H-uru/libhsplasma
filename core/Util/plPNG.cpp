/* This file is part of HSPlasma.
*
* HSPlasma is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* HSPlasma is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with HSPlasma.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "plPNG.h"
#include "Debug/plDebug.h"

#include <memory>

/* Don't know why this isn't provided by libpng itself... */
#define PNG_SIG_LENGTH (8)

/* libpng helpers */
static void pl_png_read(png_structp png, png_bytep data, png_size_t size)
{
    hsStream* S = reinterpret_cast<hsStream*>(png_get_io_ptr(png));
    S->read(size, reinterpret_cast<uint8_t*>(data));
}

static void pl_png_write(png_structp png, png_bytep data, png_size_t size)
{
    hsStream* S = reinterpret_cast<hsStream*>(png_get_io_ptr(png));
    S->write(size, reinterpret_cast<const uint8_t*>(data));
}


/* plPNG */
void plPNG::DecompressPNG(hsStream* S, void* buf, size_t size)
{
    png_structp pngReader;
    png_infop   pngInfo;
    png_infop   endInfo;

    png_byte sig[PNG_SIG_LENGTH];
    S->read(sizeof(sig), sig);
    if (!png_check_sig(sig, PNG_SIG_LENGTH))
        throw hsPNGException(__FILE__, __LINE__, "Invalid PNG header");

    pngReader = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!pngReader)
        throw hsPNGException(__FILE__, __LINE__, "Error initializing PNG reader");

    pngInfo = png_create_info_struct(pngReader);
    if (!pngInfo) {
        png_destroy_read_struct(&pngReader, nullptr, nullptr);
        throw hsPNGException(__FILE__, __LINE__, "Error initializing PNG info structure");
    }

    endInfo = png_create_info_struct(pngReader);
    if (!endInfo) {
        png_destroy_read_struct(&pngReader, &pngInfo, nullptr);
        throw hsPNGException(__FILE__, __LINE__, "Error initializing PNG info structure");
    }

    png_set_read_fn(pngReader, (png_voidp)S, &pl_png_read);
    png_set_sig_bytes(pngReader, PNG_SIG_LENGTH);

    png_read_info(pngReader, pngInfo);
    png_uint_32 pngWidth  = png_get_image_width(pngReader, pngInfo);
    png_uint_32 pngHeight = png_get_image_height(pngReader, pngInfo);
    png_uint_32 depth     = png_get_bit_depth(pngReader, pngInfo);
    png_uint_32 channels  = png_get_channels(pngReader, pngInfo);
    png_uint_32 colorType = png_get_color_type(pngReader, pngInfo);

    // Convert input to RGB
    switch (colorType) {
    case PNG_COLOR_TYPE_PALETTE:
        png_set_palette_to_rgb(pngReader);
        channels = 3;
        break;

    case PNG_COLOR_TYPE_GRAY:
        if (depth < 8)
            png_set_expand_gray_1_2_4_to_8(pngReader);
        depth = 8;
        break;

    default:
        /* Already RGB - nothing to do */
        break;
    }

    if (png_get_valid(pngReader, pngInfo, PNG_INFO_tRNS)) {
        // Convert 1-bit alpha to 8-bit alpha if necessary
        png_set_tRNS_to_alpha(pngReader);
        channels += 1;
    } else if (channels == 3) {
        // Add opaque alpha channel
        png_set_filler(pngReader, 0xFF, PNG_FILLER_AFTER);
        channels += 1;
    }

    // Plasma uses BGR for DirectX
    png_set_bgr(pngReader);

    std::unique_ptr<png_bytep[]> rows(new png_bytep[pngHeight]);
    const unsigned int stride = pngWidth * depth * channels / 8;
    png_bytep dest = reinterpret_cast<png_bytep>(buf);
    for (size_t i = 0; i < pngHeight; ++i) {
        rows[i] = dest + (i * stride);
        if (rows[i] + stride > dest + size)
            throw hsPNGException(__FILE__, __LINE__, "PNG output buffer is too small");
    }

    png_read_image(pngReader, rows.get());
    png_read_end(pngReader, endInfo);
    
    png_destroy_read_struct(&pngReader, &pngInfo, &endInfo);
}

void plPNG::CompressPNG(hsStream* S, const void* buf, size_t size,
                        uint32_t width, uint32_t height, int pixelSize)
{
    png_structp pngWriter;
    png_infop   pngInfo;

    pngWriter = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!pngWriter)
        throw hsPNGException(__FILE__, __LINE__, "Error initializing PNG writer");

    pngInfo = png_create_info_struct(pngWriter);
    if (!pngInfo) {
        png_destroy_write_struct(&pngWriter, nullptr);
        throw hsPNGException(__FILE__, __LINE__, "Error initializing PNG info structure");
    }

    png_set_write_fn(pngWriter, (png_voidp)S, &pl_png_write, nullptr);
    png_set_IHDR(pngWriter, pngInfo, width, height, 8,
                 PNG_COLOR_TYPE_RGB_ALPHA, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

    // Plasma uses BGR for DirectX
    png_set_bgr(pngWriter);

    png_write_info(pngWriter, pngInfo);

    png_bytep src = reinterpret_cast<png_bytep>(const_cast<void*>(buf));
    std::unique_ptr<png_bytep[]> rows(new png_bytep[height]);
    const unsigned int stride = width * pixelSize / 8;
    for (size_t i = 0; i < height; ++i) {
        rows[i] = src + (i * stride);
        if (rows[i] + stride > src + size)
            throw hsPNGException(__FILE__, __LINE__, "PNG input buffer is too small");
    }

    png_write_image(pngWriter, rows.get());
    png_write_end(pngWriter, pngInfo);

    png_destroy_write_struct(&pngWriter, &pngInfo);
}
