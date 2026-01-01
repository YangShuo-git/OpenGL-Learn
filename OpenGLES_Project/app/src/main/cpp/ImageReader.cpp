//
// Created by BaiYang on 2025-11-30.
//

#include "ImageReader.h"

#define STB_IMAGE_IMPLEMENTATION //必须在stb_image.h之前
extern "C"{
#include "stb_image.h"
}


ImageReader::ImageReader():m_width(0),m_height(0),m_type(0),m_pImgData(nullptr){

}

ImageReader::~ImageReader() {
    if(m_pImgData) {
        free(m_pImgData);
    }
}

int ImageReader::getWidth() const {
    return m_width;
}

int ImageReader::getHeight() const {
    return m_height;
}

int ImageReader::getType() const {
    return m_type;
}

uchar *ImageReader::getData() const {
    return m_pImgData;
}

void ImageReader::readFromFile(unsigned char *fileName) {
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

void ImageReader::readFromBuffer(uchar *dataBuff, int length) {
    int	type = 0;
    int	width = 0;
    int	height = 0;

    stbi_set_flip_vertically_on_load(true);

    uchar* picData = stbi_load_from_memory((uchar const *)dataBuff, length, &width, &height, &type, 0);
    int imgSize = width * height * 4;

    if(imgSize >0 && picData != nullptr){
        m_pImgData =(uchar*) malloc(imgSize);
        memcpy(m_pImgData,picData,imgSize);

        m_width = width;
        m_height = height;
        m_type = type;
    }

    stbi_image_free(picData);
}
