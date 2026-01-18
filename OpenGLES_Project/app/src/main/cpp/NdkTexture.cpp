//
// Created by BaiYang on 2025-11-30.
//
#define LOG_TAG "NdkRender"
#include "NdkTexture.h"

NdkTexture::NdkTexture():m_texID(-1){

}

NdkTexture::~NdkTexture() {

}

GLuint NdkTexture::getTextureID() {
    return m_texID;
}

GLuint NdkTexture::generateTexture(AAssetManager *assetManager, const char *fileName) {
    return 0;
}

GLuint NdkTexture::createTextureFromFile(AAssetManager *assetManager, const char *fileName) {
    AAsset *asset = AAssetManager_open(assetManager, fileName, AASSET_MODE_UNKNOWN);
    if (nullptr == asset){
        LOGE("asset is nullptr");
        return -1;
    }
    off_t bufferSize = AAsset_getLength(asset);
    LOGD("buffer size is %ld", bufferSize);

    unsigned char *imgBuff = (unsigned char *)malloc(bufferSize + 1);
    if (nullptr == imgBuff){
        LOGE("imgBuff alloc failed");
        return -1;
    }
    memset(imgBuff, 0, bufferSize + 1);
    int readLen = AAsset_read(asset, imgBuff, bufferSize);
    LOGI("Picture read: %d", readLen);

    Imageloader* pImgLoader = new Imageloader();
    pImgLoader->readFromBuffer(imgBuff,readLen);

    // 获取管理图片数据的纹理索引
    GLuint textureID = createOpenGLTexture(pImgLoader);

    delete pImgLoader;
    if (imgBuff){
        free(imgBuff);
        imgBuff = nullptr;
    }
    AAsset_close(asset);

    return textureID;
}

GLuint NdkTexture::createOpenGLTexture(Imageloader *pImgLoader) {
    if(pImgLoader == nullptr){
        return -1;
    }

    GLuint textureID;

    glEnable(GL_TEXTURE_2D);
    glGenTextures(1,&textureID);//生成纹理索引，用来管理图片数据
    glBindTexture(GL_TEXTURE_2D,textureID);//绑定纹理索引，之后的操作都针对该纹理索引

    //配置参数，告诉GPU当纹理被拉伸、缩小或超出坐标范围时该如何处理
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    //先从ImgLoader中获取图片数据，然后传输到GPU的显存中，可以根据当前的纹理索引来处理图片数据
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,
                 pImgLoader->getWidth(),pImgLoader->getHeight(),0,
                 GL_RGBA,GL_UNSIGNED_BYTE,pImgLoader->getData());
    glBindTexture(GL_TEXTURE_2D, 0); //不加该行，也不会报错

    return textureID;
}
