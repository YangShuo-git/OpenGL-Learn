//
// Created by BaiYang on 2025-11-30.
//

#ifndef OPENGLES_PROJECT_NDKRENDER_H
#define OPENGLES_PROJECT_NDKRENDER_H

#include "CommonDef.h"

#include "NdkTexture.h"
#include "NdkBuffer.h"
#include "NdkShader.h"
#include "NdkVAO.h"
#include "NdkFBO.h"

class NdkRender {
public:
    NdkRender();
    ~NdkRender();

    void init();
    void draw();
    void sizeChanged(int w, int h);

    void setAssetManager(AAssetManager *pManager);

    void drawTriangle();
    void drawRectangle();
    void drawPoint();
    void drawLine();
    void drawPicture();

    void drawTriangle3();

    void setupDrawingRect();
    void drawRect();

    void setupDrawingCube();
    void drawCube();

    void setupDrawingEffect();
    void drawTransition();
    void drawEffect();


private:
    void loadTextureResources(AAssetManager *pManager);
    void loadShaderResources(AAssetManager *pManager);

private:
    float m_nValue = 0.0f;
    float m_angle = 0.0f;
    GLuint m_texID[6];

    AAssetManager *m_pAssetManager;

    NdkVAO*    m_pVAO;
    NdkBuffer* m_pVBO;
    NdkBuffer* m_pEBO;
    NdkFBO*    m_pFBO;

    NdkShader* m_pShader;
};

#endif //OPENGLES_PROJECT_NDKRENDER_H
