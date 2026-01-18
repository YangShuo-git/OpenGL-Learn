//
// Created by BaiYang on 2025-11-30.
//

#include "Imageloader.h"

#define STB_IMAGE_IMPLEMENTATION //必须在stb_image.h之前
extern "C"{
#include "stb_image.h"
}


Imageloader::Imageloader(): m_width(0), m_height(0), m_type(0), m_pImgData(nullptr){

}

Imageloader::~Imageloader() {
    if(m_pImgData) {
        free(m_pImgData);
    }
}

int Imageloader::getWidth() const {
    return m_width;
}

int Imageloader::getHeight() const {
    return m_height;
}

int Imageloader::getType() const {
    return m_type;
}

uchar *Imageloader::getData() const {
    return m_pImgData;
}

void Imageloader::readFromFile(unsigned char *fileName) {
    int			type = 0;
    int			width = 0;
    int			height = 0;

    //stbi_set_flip_vertically_on_load(true);

    uchar* picData = stbi_load((char const *)fileName, &width, &height, &type, STBI_rgb_alpha);
    int imgSize = width * height * 4;
    if(imgSize >0 && picData != nullptr){
        m_pImgData =(uchar*) malloc(imgSize);
        memcpy(m_pImgData,picData,imgSize);

        m_width =width;
        m_height =height;
        m_type = type;
    }

    stbi_image_free(picData);
}

void Imageloader::readFromBuffer(uchar *dataBuff, int length) {
    int	type = 0;
    int	width = 0;
    int	height = 0;

    stbi_set_flip_vertically_on_load(true);

    uchar* picData = stbi_load_from_memory((uchar const *)dataBuff, length, &width, &height, &type, 0);
    int imgSize = width * height * 4;

    LOGI("readFromBuffer: %d, %d, %d", width, height, type);
    if(imgSize >0 && picData != nullptr){
        m_pImgData =(uchar*) malloc(imgSize);
        memcpy(m_pImgData,picData,imgSize);

        m_width = width;
        m_height = height;
        m_type = type;
    }

    stbi_image_free(picData);
}
