//
// Created by BaiYang on 2025-11-30.
//
#define LOG_TAG "NdkRender"
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

//    drawTriangle();
//    drawRectangle();
//    drawPoint();
//    drawLine();
    drawPicture();
}

void NdkRender::sizeChanged(int w, int h) {
    glViewport(0,0,w,h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrthof(-1,1,-1,1,0.1,1000.0);
//    glFrustumf(-1,1,-1,1,0.1,1000.0);
}

void NdkRender::setAssetManager(AAssetManager *pManager) {
    if(pManager == nullptr){
        return;
    }
    m_pAssetManager = pManager;
}

void NdkRender::loadTextureResources(AAssetManager *pManager) {
    NdkTexture glTexture;
    m_texID[0] = glTexture.createTextureFromFile(pManager, "earth.png");
//    for(int i=1; i<6; i++){
//        char nameBuff[6];
//        memset(nameBuff,0,sizeof(nameBuff));
//        sprintf(nameBuff,"%d.png",i+1);
//        nameBuff[5]='\0';
//        LOGD("Image Name:%s",nameBuff);
//        NdkTexture glTexture;
//        m_texID[i] = glTexture.createTextureFromFile(pManager,nameBuff);
//    }
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

void NdkRender::drawRectangle() {
    PriFloat7 vertexTriangle[] ={
            {-0.5,-0.1,-0.1,1.0,0.0,0.0,1.0},
            {-0.5,-0.8,-0.1,0.0,1.0,0.0,1.0},
            {0.5,-0.1,-0.1,0.0,0.0,1.0,1.0},
            {0.5,-0.8,-0.1,1.0,0.0,1.0,1.0},
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3,GL_FLOAT,sizeof(PriFloat7),vertexTriangle);

    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(4, GL_FLOAT, sizeof(PriFloat7),&vertexTriangle[0].r);

    glDrawArrays(GL_TRIANGLE_STRIP,0,4);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void NdkRender::drawPoint() {
    PriFloat3 vertexTriangle[] ={
            {-0.5,-0.5,-0.1},
            {-0.5,0.5,-0.1},
            {0.5,-0.5,-0.1},
            {0.5,0.5,-0.1},
    };

    glColor4f(1.0, 1.0, 1.0, 1.0);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3,GL_FLOAT,sizeof(PriFloat3),vertexTriangle);

    glPointSize(20);
    glEnable(GL_POINT_SMOOTH);  //不使用smooth，会画出正方形
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

    glDrawArrays(GL_POINTS,0,4);

    glDisableClientState(GL_VERTEX_ARRAY);
}

void NdkRender::drawLine() {
    PriFloat3 vertexTriangle[] ={
            {-0.5,-0.5,-0.1},
            {-0.5,0.5,-0.1},
            {0.5,-0.5,-0.1},
            {0.5,0.5,-0.1},
    };

    glColor4f(1.0, 1.0, 1.0, 1.0);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3,GL_FLOAT,sizeof(PriFloat3),vertexTriangle);

    glLineWidth(4);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

    glDrawArrays(GL_LINE_LOOP,0,4);

    glDisableClientState(GL_VERTEX_ARRAY);
}

void NdkRender::drawPicture() {
    PriFloat5 planVertices[] =
            {
            { -1.0f, -1.0f, 1.0f, 0, 0 },
            { -1.0f, 1.0f, 1.0f, 0, 1 },
            { 1.0f, -1.0f, 1.0f, 1, 0 },
            { 1.0f, 1.0f, 1.0f, 1, 1 },
            };

    glBindTexture(GL_TEXTURE_2D, m_texID[0]);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glVertexPointer(3,GL_FLOAT,sizeof(PriFloat5),planVertices);
    glTexCoordPointer(2,GL_FLOAT,sizeof(PriFloat5),&planVertices[0].u);

    glm::mat4x4  cubeMat;
    glm::mat4x4  cubeTransMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -0.5));
    glm::mat4x4  cubeRotMat   = glm::rotate(glm::mat4(1.0f),m_angle,glm::vec3(0.5f, 0.5f, 1.0) );
    glm::mat4x4  cubeScaleMat = glm::scale(glm::mat4(1.0f),glm::vec3(0.5f, 0.3f, 0.1) );
    cubeMat = cubeTransMat * cubeRotMat * cubeScaleMat;
    glLoadMatrixf(glm::value_ptr(cubeMat));

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}
