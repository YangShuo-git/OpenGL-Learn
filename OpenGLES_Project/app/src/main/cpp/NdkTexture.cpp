//
// Created by BaiYang on 2025-11-30.
//

#include "NdkTexture.h"

NdkTexture::NdkTexture():m_texID(-1){

}

NdkTexture::~NdkTexture() {

}

GLuint NdkTexture::getTextureID() {
    return m_texID;
}

GLuint NdkTexture::createTextureFromFile(AAssetManager *assetManager, const char *fileName) {
    m_texID = generateTexture(assetManager, fileName);
    return m_texID;
}

GLuint NdkTexture::generateTexture(AAssetManager *assetManager, const char *fileName) {
    AAsset *asset = AAssetManager_open (assetManager, fileName, AASSET_MODE_UNKNOWN);
    if (nullptr == asset){
        LOGF("asset is nullptr");
        return -1;
    }
    off_t bufferSize = AAsset_getLength(asset);
    LOGD("buffer size is %ld", bufferSize);

    unsigned char *imgBuff = (unsigned char *)malloc(bufferSize + 1);
    if (nullptr == imgBuff){
        LOGF("imgBuff alloc failed");
        return -1;
    }
    memset(imgBuff, 0, bufferSize + 1);
    int readLen = AAsset_read(asset, imgBuff, bufferSize);
    LOGD("Picture read: %d", readLen);

    ImageReader* pImageReader = new ImageReader();
    pImageReader->readFromBuffer(imgBuff,readLen);
    GLuint texID = createOpenGLTexture(pImageReader);

    delete pImageReader;

    if (imgBuff){
        free(imgBuff);
        imgBuff = nullptr;
    }

    AAsset_close(asset);

    return texID;
}

GLuint NdkTexture::createOpenGLTexture(ImageReader *pImgReader) {
    if(pImgReader == nullptr){
        return -1;
    }

    GLuint textureID;
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1,&textureID);//产生纹理索引
    glBindTexture(GL_TEXTURE_2D,textureID);//绑定纹理索引，之后的操作都针对当前纹理索引

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);//当纹理图象被使用到一个大于它的形状上时
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);//当纹理图象被使用到一个小于或等于它的形状上时
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,
                 pImgReader->getWidth(),pImgReader->getHeight(),0,
                 GL_RGBA,GL_UNSIGNED_BYTE,pImgReader->getData());//指定参数，生成纹理

    return textureID;
}
