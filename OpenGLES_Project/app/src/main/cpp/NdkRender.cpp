//
// Created by BaiYang on 2025-11-30.
//

#include "NdkRender.h"
#include "NdkTexture.h"

NdkRender::NdkRender():m_pAssetManager(nullptr) {

}

NdkRender::~NdkRender() {
    glDeleteTextures(6,m_texID);
}

void NdkRender::init() {
    glClearColor(0.0,0.0,0.0,1.0);
    glClearDepthf(1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    if(m_pAssetManager != nullptr){
        loadTextureResources(m_pAssetManager);
    }
}

void NdkRender::draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    drawTriangle();
}

void NdkRender::sizeChanged(int w, int h) {
    glViewport(0,0,w,h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrthof(-1,1,-1,1,0.1,1000.0);
//    glFrustumf(-1,1,-1,1,0.1,1000.0);
}

void NdkRender::setupAssetManager(AAssetManager *pManager) {
    if(pManager == nullptr){
        return;
    }
    m_pAssetManager = pManager;
}

void NdkRender::loadTextureResources(AAssetManager *pManager) {
    for(int i=0; i<6; i++){

        char nameBuff[6];
        memset(nameBuff,0,sizeof(nameBuff));
        sprintf(nameBuff,"%d.png",i+1);
        nameBuff[5]='\0';
        LOGD("Image Name:%s",nameBuff);
        NdkTexture glTexture;
        m_texID[i] = glTexture.createTextureFromFile(pManager,nameBuff);
    }
}

void NdkRender::loadShaderResources(AAssetManager *pManager) {

}

void NdkRender::drawTriangle() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    PriFloat7 vertexTriangle[] ={
            {0.5,0.1,-0.1,1.0,0.0,0.0,1.0},
            {0.5,0.5,-0.1,0.0,1.0,0.0,1.0},
            {-0.5,0.1,-0.1,0.0,0.0,1.0,1.0},
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3,GL_FLOAT,sizeof(PriFloat7),vertexTriangle);

    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(4, GL_FLOAT, sizeof(PriFloat7),&vertexTriangle[0].r);

    m_angle += 0.01f; //旋转速度

    glm::mat4x4  cubeMat;
    glm::mat4x4  cubeTransMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -0.5));           //平移
    glm::mat4x4  cubeRotMat   = glm::rotate(glm::mat4(1.0f),m_angle,glm::vec3(0.5f, 0.5f, 1.0) ); //旋转
    glm::mat4x4  cubeScaleMat = glm::scale(glm::mat4(1.0f),glm::vec3(0.5f, 0.4f, 0.1) );                //缩放
    cubeMat = cubeTransMat * cubeRotMat * cubeScaleMat;

    glLoadMatrixf(glm::value_ptr(cubeMat));

    glDrawArrays(GL_TRIANGLES,0,3);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}
