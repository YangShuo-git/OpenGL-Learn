//
// Created by BaiYang on 2025-11-30.
//

#ifndef OPENGLES_PROJECT_NDKTEXTURE_H
#define OPENGLES_PROJECT_NDKTEXTURE_H

#include "CommonDef.h"
#include "ImageReader.h"

class NdkTexture {
public:
    NdkTexture();
    ~NdkTexture();

    GLuint  getTextureID();
    GLuint  createTextureFromFile(AAssetManager *assetManager, const char* fileName);

private:
    GLuint  generateTexture(AAssetManager *assetManager, const char* fileName);
    GLuint  createOpenGLTexture(ImageReader* pImgReader);

private:
    GLuint m_texID;
};


#endif //OPENGLES_PROJECT_NDKTEXTURE_H
