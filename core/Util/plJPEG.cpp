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

#include "plJPEG.h"
#include "Debug/plDebug.h"
#include "PRP/Surface/plMipmap.h"
#include <cstring>

extern "C" {
#include <jerror.h>
}


// Input Stream interface

#define INPUT_BUF_SIZE  4096

/* hsStream JPEG source -- modelled after IJG's stdio src */
typedef struct
{
    struct jpeg_source_mgr pub;
    hsStream* stream;
    JOCTET* buffer;
    boolean start_of_stream;
} jpeg_hsStream_source;

METHODDEF(void) init_hsStream_source(j_decompress_ptr dinfo)
{
    jpeg_hsStream_source* src = (jpeg_hsStream_source*)dinfo->src;
    src->start_of_stream = TRUE;
}

METHODDEF(boolean) hsStream_fill_input_buffer(j_decompress_ptr dinfo)
{
    jpeg_hsStream_source* src = (jpeg_hsStream_source*)dinfo->src;
    size_t nbytes = INPUT_BUF_SIZE;

    if (src->stream->pos() + nbytes > src->stream->size())
        nbytes = src->stream->size() - src->stream->pos();
    src->stream->read(nbytes, src->buffer);

    if (nbytes <= 0) {
        if (src->start_of_stream)
            throw hsJPEGException(__FILE__, __LINE__, "JPEG Decompress error: Input buffer is empty");
        WARNMS(dinfo, JWRN_JPEG_EOF);

        /* Insert a fake EOI marker */
        src->buffer[0] = (JOCTET)0xFF;
        src->buffer[1] = (JOCTET)JPEG_EOI;
        nbytes = 2;
    }

    src->pub.next_input_byte = src->buffer;
    src->pub.bytes_in_buffer = nbytes;
    src->start_of_stream = FALSE;

    return TRUE;
}

METHODDEF(void) hsStream_skip_input_data(j_decompress_ptr dinfo, long num_bytes)
{
    jpeg_hsStream_source* src = (jpeg_hsStream_source*)dinfo->src;

    if (num_bytes > 0) {
        while (num_bytes > (long)src->pub.bytes_in_buffer) {
            num_bytes -= (long)src->pub.bytes_in_buffer;
            hsStream_fill_input_buffer(dinfo);
        }
        src->pub.next_input_byte += (size_t)num_bytes;
        src->pub.bytes_in_buffer -= (size_t)num_bytes;
    }
}

METHODDEF(void) hsStream_term_source(j_decompress_ptr dinfo) { }

GLOBAL(void) jpeg_hsStream_src(j_decompress_ptr dinfo, hsStream* S)
{
    jpeg_hsStream_source* src;

    if (dinfo->src == nullptr) {
        dinfo->src = (struct jpeg_source_mgr*)
            (*dinfo->mem->alloc_small)((j_common_ptr)dinfo, JPOOL_PERMANENT,
                                       sizeof(jpeg_hsStream_source));
        src = (jpeg_hsStream_source*)dinfo->src;
        src->buffer = (JOCTET *)
            (*dinfo->mem->alloc_small)((j_common_ptr)dinfo, JPOOL_PERMANENT,
                                       INPUT_BUF_SIZE * sizeof(JOCTET));
    }

    src = (jpeg_hsStream_source*)dinfo->src;
    src->pub.init_source = init_hsStream_source;
    src->pub.fill_input_buffer = hsStream_fill_input_buffer;
    src->pub.skip_input_data = hsStream_skip_input_data;
    src->pub.resync_to_restart = jpeg_resync_to_restart;
    src->pub.term_source = hsStream_term_source;
    src->stream = S;
    src->pub.bytes_in_buffer = 0;
    src->pub.next_input_byte = nullptr;
}


// Output Stream interface

#define OUTPUT_BUF_SIZE  4096

/* hsStream JPEG destination -- modelled after IJG's stdio dest */
typedef struct
{
    struct jpeg_destination_mgr pub;
    hsStream* stream;
    JOCTET* buffer;
    boolean start_of_stream;
} jpeg_hsStream_destination;

METHODDEF(void) init_hsStream_destination(j_compress_ptr cinfo)
{
    jpeg_hsStream_destination* dest = (jpeg_hsStream_destination*)cinfo->dest;
    dest->start_of_stream = TRUE;
}

METHODDEF(boolean) hsStream_empty_output_buffer(j_compress_ptr cinfo)
{
    jpeg_hsStream_destination* dest = (jpeg_hsStream_destination*)cinfo->dest;

    dest->stream->write(OUTPUT_BUF_SIZE, dest->buffer);

    memset(dest->buffer, 0, OUTPUT_BUF_SIZE);

    dest->pub.next_output_byte = dest->buffer;
    dest->pub.free_in_buffer = OUTPUT_BUF_SIZE;
    dest->start_of_stream = FALSE;

    return TRUE;
}

METHODDEF(void) hsStream_term_destination(j_compress_ptr cinfo)
{ 
    jpeg_hsStream_destination* dest = (jpeg_hsStream_destination*)cinfo->dest;
    size_t datacount = OUTPUT_BUF_SIZE - dest->pub.free_in_buffer;
    if (datacount > 0)
        dest->stream->write(datacount, dest->buffer);
    dest->stream->flush();
}

GLOBAL(void) jpeg_hsStream_dest(j_compress_ptr cinfo, hsStream* S)
{
    jpeg_hsStream_destination* dest;

    if (cinfo->dest == nullptr) {
        cinfo->dest = (struct jpeg_destination_mgr*)
            (*cinfo->mem->alloc_small)((j_common_ptr)cinfo, JPOOL_PERMANENT,
                sizeof(jpeg_hsStream_destination));
        dest = (jpeg_hsStream_destination*)cinfo->dest;
        dest->buffer = (JOCTET*)
            (*cinfo->mem->alloc_small)((j_common_ptr)cinfo, JPOOL_PERMANENT,
                OUTPUT_BUF_SIZE * sizeof(JOCTET));
    }

    dest = (jpeg_hsStream_destination*)cinfo->dest;
    dest->pub.init_destination = init_hsStream_destination;
    dest->pub.empty_output_buffer = hsStream_empty_output_buffer;
    dest->pub.term_destination = hsStream_term_destination;
    dest->stream = S;
    dest->pub.free_in_buffer = OUTPUT_BUF_SIZE;
    dest->pub.next_output_byte = dest->buffer;
}

// JPEG error handler for libPlasma
static char jpeg_error_buf[JMSG_LENGTH_MAX] = { 0 };

METHODDEF(void) plasma_output_message(j_common_ptr cinfo)
{
    (*cinfo->err->format_message)(cinfo, jpeg_error_buf);
    plDebug::Error(jpeg_error_buf);
}

METHODDEF(void) plasma_error_exit(j_common_ptr cinfo)
{
    (*cinfo->err->output_message)(cinfo);
    jpeg_destroy(cinfo);
    throw hsJPEGException(__FILE__, __LINE__, jpeg_error_buf);
}


/* plJPEG */
plJPEG& plJPEG::Instance()
{
    static plJPEG s_instance;
    return s_instance;
}

plJPEG::plJPEG()
{
    cinfo.err = jpeg_std_error(&jerr);
    dinfo.err = cinfo.err;
    cinfo.err->error_exit = plasma_error_exit;
    cinfo.err->output_message = plasma_output_message;

    jpeg_create_compress(&cinfo);
    jpeg_create_decompress(&dinfo);
}

plJPEG::~plJPEG()
{
    jpeg_destroy_compress(&cinfo);
    jpeg_destroy_decompress(&dinfo);
}

template <size_t _Rows>
struct RAII_JSAMPROW
{
    JSAMPROW data[_Rows];

    RAII_JSAMPROW(int row_stride)
    {
        for (size_t i = 0; i < _Rows; ++i)
            data[i] = new JSAMPLE[row_stride];
    }

    ~RAII_JSAMPROW()
    {
        for (size_t i = 0; i < _Rows; ++i)
            delete[] data[i];
    }
};

void plJPEG::DecompressJPEG(hsStream* S, void* buf, size_t size)
{
    plJPEG& ji = Instance();

    jpeg_hsStream_src(&ji.dinfo, S);
    jpeg_read_header(&ji.dinfo, TRUE);
    ji.dinfo.out_color_space = JCS_EXT_BGRA;    // Data stored as RGB on disk but Plasma uses BGR
    jpeg_start_decompress(&ji.dinfo);

    int row_stride = ji.dinfo.output_width * ji.dinfo.out_color_components;
    int out_stride = row_stride;
    RAII_JSAMPROW<1> jbuffer(row_stride);

    size_t offs = 0;
    while (ji.dinfo.output_scanline < ji.dinfo.output_height) {
        if (offs + out_stride > size)
            throw hsJPEGException(__FILE__, __LINE__, "buffer overflow");
        jpeg_read_scanlines(&ji.dinfo, jbuffer.data, 1);
        for (size_t x = 0; x<ji.dinfo.output_width; x++) {
            memcpy(((unsigned char*)buf) + offs + (x * 4),
                   jbuffer.data[0] + (x * ji.dinfo.out_color_components),
                   ji.dinfo.out_color_components);
        }
        offs += out_stride;
    }

    jpeg_finish_decompress(&ji.dinfo);
}


plMipmap* plJPEG::DecompressJPEG(hsStream* S)
{
    plJPEG& ji = Instance();

    jpeg_hsStream_src(&ji.dinfo, S);
    jpeg_read_header(&ji.dinfo, TRUE);
    ji.dinfo.out_color_space = JCS_EXT_BGRA;    // Data stored as RGB on disk but Plasma uses BGR
    jpeg_start_decompress(&ji.dinfo);

    int row_stride = ji.dinfo.output_width * ji.dinfo.out_color_components;
    int out_stride = row_stride;
    RAII_JSAMPROW<1> jbuffer(row_stride);

    // Start with a reasonable size for the buffer
    std::vector<uint8_t> buffer(ji.dinfo.output_width * ji.dinfo.output_height * ji.dinfo.out_color_components);

    size_t offs = 0;
    while (ji.dinfo.output_scanline < ji.dinfo.output_height) {
        while (offs + out_stride > buffer.capacity()) {
            buffer.reserve(buffer.capacity() + INPUT_BUF_SIZE);
        }
        jpeg_read_scanlines(&ji.dinfo, jbuffer.data, 1);
        for (size_t x = 0; x < ji.dinfo.output_width; x++) {
            memcpy(((unsigned char*)buffer.data()) + offs + (x * 4),
                jbuffer.data[0] + (x * ji.dinfo.out_color_components),
                ji.dinfo.out_color_components);
        }
        offs += out_stride;
    }

    jpeg_finish_decompress(&ji.dinfo);
    buffer.shrink_to_fit();

    plMipmap* newMipmap = new plMipmap(ji.dinfo.output_width, ji.dinfo.output_height, 1, plMipmap::kUncompressed, plMipmap::kRGB8888);
    newMipmap->setImageData(buffer.data(), buffer.size());

    return newMipmap;
}

void plJPEG::CompressJPEG(hsStream* S, void* buf, size_t size, uint32_t width, uint32_t height, uint32_t bpp)
{
    plJPEG& ji = Instance();

    JSAMPLE* image_buffer = reinterpret_cast<JSAMPLE*>(buf);

    jpeg_create_compress(&ji.cinfo);
    jpeg_hsStream_dest(&ji.cinfo, S);

    ji.cinfo.image_width = width;
    ji.cinfo.image_height = height;
    ji.cinfo.input_components = bpp / 8;
    if (ji.cinfo.input_components == 4)
        ji.cinfo.in_color_space = JCS_EXT_RGBX;
    else
        ji.cinfo.in_color_space = JCS_RGB;

    jpeg_set_defaults(&ji.cinfo);
    jpeg_set_quality(&ji.cinfo, 100, TRUE);
    jpeg_start_compress(&ji.cinfo, TRUE);
    
    uint32_t row_stride = ji.cinfo.image_width * ji.cinfo.input_components;
    RAII_JSAMPROW<1> jbuffer(row_stride);

    size_t offs = 0;
    while (ji.cinfo.next_scanline < ji.cinfo.image_height) {
        if (offs + row_stride > size)
            throw hsJPEGException(__FILE__, __LINE__, "buffer overread");

        for (size_t x = 0; x < ji.cinfo.image_width; x++) {
            memcpy(jbuffer.data[0] + (x * ji.cinfo.input_components),
                   ((unsigned char*)image_buffer) + offs + (x * ji.cinfo.input_components),
                   ji.cinfo.input_components);
        }
        (void)jpeg_write_scanlines(&ji.cinfo, jbuffer.data, 1);
        offs += row_stride;
    }

    jpeg_finish_compress(&ji.cinfo);
    jpeg_destroy_compress(&ji.cinfo);
}
