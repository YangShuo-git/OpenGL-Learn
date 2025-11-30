//
// Created by BaiYang on 2025-11-09.
//

#include "com_example_opengles_project_GLRender.h"
#include <android/asset_manager_jni.h>
#include <android/asset_manager.h>

#include "Log.h"
#include "GLPrimitives.h"
#include "ImageReader.h"

#ifdef __cplusplus
extern "C" {
#endif

GLuint createOpenGLTexture(ImageReader* pImg)
{
    if(pImg == NULL){
        return -1;
    }

    GLuint textureID; //纹理索引
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1,&textureID);
    glBindTexture(GL_TEXTURE_2D,textureID);//绑定纹理索引，之后的操作都针对当前纹理索引

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);//当纹理图象被使用到一个大于它的形状上时
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);//当纹理图象被使用到一个小于或等于它的形状上时
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,
                 pImg->GetWidth(),pImg->GetHeight(),
                 0,GL_RGBA,GL_UNSIGNED_BYTE,
                 pImg->GetData());//指定参数，生成纹理

    return textureID;
}

void Java_com_example_opengles_1project_GLRender_n_1initGL(JNIEnv *, jobject) {
    glClearColor(0.0,0.0,0.0,1.0);
    glClearDepthf(1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    LOGD("OpenGL init");
}

void Java_com_example_opengles_1project_GLRender_n_1drawGL(JNIEnv *, jobject){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    drawPicture();

//    drawTriangle();
//    drawRectangle();
//    drawLine();
//    drawPoint();
}

void Java_com_example_opengles_1project_GLRender_n_1changeSizeGL(JNIEnv *, jobject, jint width, jint height){
    glViewport(0,0,width,height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //正交投影 相当于摄像机  n是朝里，但z是朝外，所以0.1和-0.1是在一个平面  n<0.1时，该摄像机能拍到物体
    glOrthof(-1,1,-1,1,0.1,1000.0);

    LOGI("OpenGL change size: %d, %d", width, height);
}

int Java_com_example_opengles_1project_GLRender_n_1readAssetFile
        (JNIEnv *env, jobject obj, jobject assetManager, jstring fName) {
    AAssetManager *mAssetManager = AAssetManager_fromJava (env, assetManager);
    if (NULL == mAssetManager){
        LOGE("assetManager is NULL");
        return -1;
    }
    const char *fileName = env->GetStringUTFChars(fName, 0);
    if (NULL == fileName){
        LOGE("fileName is NULL");
        return -1;
    }
    LOGI("FileName is %s", fileName);
    AAsset *asset = AAssetManager_open(mAssetManager, fileName, AASSET_MODE_UNKNOWN);
    if (NULL == asset){
        LOGE("asset is NULL");
        return -1;
    }
    off_t bufferSize = AAsset_getLength(asset);
    LOGD("buffer size is %ld", bufferSize);

    unsigned char *imgBuff = (unsigned char *)malloc(bufferSize + 1);
    if (NULL == imgBuff){
        LOGE("imgBuff alloc failed");
        return -1;
    }
    memset(imgBuff, 0, bufferSize + 1);
    int readLen = AAsset_read(asset, imgBuff, bufferSize);
    LOGD("Picture read: %d", readLen);

    ImageReader* glImage = ImageReader::ReadFromBuffer(imgBuff,readLen);
    g_texID = createOpenGLTexture(glImage);

    delete glImage;
    if (imgBuff){
        free(imgBuff);
        imgBuff = NULL;
    }

    AAsset_close(asset);
    env->ReleaseStringUTFChars(fName, fileName);

    return 0;
}

#ifdef __cplusplus
}
#endif
