#include "plJPEG.h"

plJPEG* plJPEG::inst = NULL;

plJPEG::plJPEG() {
    if (inst != NULL)
        throw "Never construct me more than once!";
    inst = this;

    cinfo.err = jpeg_std_error(&jerr);
    dinfo.err = cinfo.err;
    jpeg_create_compress(&cinfo);
    jpeg_create_decompress(&dinfo);
}

plJPEG::~plJPEG() {
    jpeg_destroy_compress(&cinfo);
    jpeg_destroy_decompress(&dinfo);

    inst = NULL;
}

/*extern "C" {

JOCTET* jpSrcBuffer;
unsigned int jpSize;

void jpMgr_init_source(j_decompress_ptr cinfo) {
    cinfo->src->next_input_byte = jpSrcBuffer;
    cinfo->src->bytes_in_buffer = jpSize;
}

boolean jpMgr_fill_input_buffer(j_decompress_ptr cinfo) {
    return TRUE;
}

void jpMgr_skip_input_data(j_decompress_ptr cinfo, long num_bytes) {
    if (num_bytes > 0) {
        cinfo->src->next_input_byte += num_bytes;
        cinfo->src->bytes_in_buffer -= num_bytes;
    }
}

void jpMgr_term_source(j_decompress_ptr cinfo) { }

}*/

plMipmap* plJPEG::IRead(hsStream* S) {
    plMipmap* newMipmap = NULL;
    //jpSize = S->readInt();
    //jpSrcBuffer = (JOCTET*)malloc(jpSize);
    //S->read(jpSize, jpSrcBuffer);

    /*
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);
    
    cinfo.src = (jpeg_source_mgr*)malloc(sizeof(jpeg_source_mgr));
    cinfo.src->next_input_byte = jpSrcBuffer;
    cinfo.src->bytes_in_buffer = jpSize;
    cinfo.src->init_source = &jpMgr_init_source;
    cinfo.src->fill_input_buffer = &jpMgr_fill_input_buffer;
    cinfo.src->skip_input_data = &jpMgr_skip_input_data;
    cinfo.src->resync_to_restart = &jpeg_resync_to_restart;
    cinfo.src->term_source = &jpMgr_term_source;
    
    jpeg_read_header(&cinfo, TRUE);
    newMipmap = new plMipmap(cinfo.image_width, cinfo.image_height,
                             plMipmap::kRGB32Config, 1,
                             plBitmap::kJPEGCompression,
                             plBitmap::UncompressedInfo::kRGB8888, S->getVer());
    jpeg_start_decompress(&cinfo);
    jpeg_finish_decompress(&cinfo);
    
    free(cinfo.src);
    jpeg_destroy_decompress(&cinfo);
    */
    //free(jpSrcBuffer);
    return newMipmap;
}

void plJPEG::IWrite(plMipmap* source, hsStream* S) {
    S->writeInt(source->getJPEGSize());
    S->write(source->getJPEGSize(), source->getJPEGData());
}

