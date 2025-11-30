//
// Created by BaiYang on 2025-11-29.
//

#ifndef OPENGLES_PROJECT_IMAGEREADER_H
#define OPENGLES_PROJECT_IMAGEREADER_H


#define STB_IMAGE_IMPLEMENTATION

#include <stdlib.h>
#include <string.h>

extern "C"{
#include "stb_image.h"
}


#ifndef uchar
#define uchar unsigned char
#endif


class ImageReader
{
public:
    ImageReader(int w, int h,int type, uchar* imgData){
        m_width =w;
        m_height =h;
        m_type = type;

        int imgSize = m_width * m_height * 4;
        if(imgSize >0 && imgData != nullptr){
            m_pImgData =(uchar*) malloc(imgSize);
            memcpy(m_pImgData,imgData,imgSize);
        }else{
            m_pImgData = NULL;
        }
    }
    ~ImageReader(){
        if(m_pImgData){
            free(m_pImgData);
        }
    }

    static ImageReader* ReadFromFile(const char* fileName){
        int			type = 0;
        int			width = 0;
        int			height = 0;

        //stbi_set_flip_vertically_on_load(true);
        uchar* picData = stbi_load(fileName, &width, &height, &type, STBI_rgb_alpha);
        ImageReader* image = new ImageReader(width, height, type, (uchar*)picData);

        stbi_image_free(picData);

        return image;
    }

    static ImageReader* ReadFromBuffer(unsigned char * dataBuff,int length){
        int			type = 0;
        int			width = 0;
        int			height = 0;

        //解决加载图片上下颠倒的问题
        stbi_set_flip_vertically_on_load(true);

        uchar* picData = stbi_load_from_memory(dataBuff, length, &width, &height, &type, 0);
        ImageReader* image = new ImageReader(width, height, type, (uchar*)picData);

        stbi_image_free(picData);

        return image;
    }

    int GetWidth() const {return m_width; }
    int GetHeight() const { return m_height; }
    int GetType() const {return m_type; }
    uchar* GetData() const { return m_pImgData; }

private:
    int     m_width    = 0;
    int     m_height   = 0;
    int     m_type     = 0;
    uchar*   m_pImgData = NULL;
};

#endif //OPENGLES_PROJECT_IMAGEREADER_H
