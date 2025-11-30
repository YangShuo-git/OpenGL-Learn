//
// Created by BaiYang on 2025-11-29.
//

#ifndef OPENGLES_PROJECT_IMAGEREADER_H
#define OPENGLES_PROJECT_IMAGEREADER_H

#include <stdlib.h>
#include <string.h>

#ifndef uchar
#define uchar unsigned char
#endif

class ImageReader
{
public:
    ImageReader();
    ~ImageReader();

    int getWidth() const;
    int getHeight() const;
    int getType() const;
    uchar* getData() const;

    void readFromFile(uchar* fileName);
    void readFromBuffer(uchar* dataBuff, int length);

private:
    int m_width;
    int m_height;
    int m_type;
    uchar* m_pImgData;
};

#endif //OPENGLES_PROJECT_IMAGEREADER_H
