//
// Created by BaiYang on 2025-11-30.
//

#ifndef OPENGLES_PROJECT_NDKRENDER_H
#define OPENGLES_PROJECT_NDKRENDER_H

#include "CommonDef.h"
#include "NdkTexture.h"
#include "NdkBuffer.h"
#include "NdkShader.h"

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

private:
    void loadTextureResources(AAssetManager *pManager);
    void loadShaderResources(AAssetManager *pManager);

private:
    float m_angle = 0.0f;
    GLuint m_texID[6];

    AAssetManager *m_pAssetManager;

    NdkBuffer* m_pVBO;
    NdkBuffer* m_pEBO;

    NdkShader* m_pShader;
};


#endif //OPENGLES_PROJECT_NDKRENDER_H
