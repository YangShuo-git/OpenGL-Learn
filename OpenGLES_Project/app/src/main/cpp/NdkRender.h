//
// Created by BaiYang on 2025-11-30.
//

#ifndef OPENGLES_PROJECT_NDKRENDER_H
#define OPENGLES_PROJECT_NDKRENDER_H

#include "CommonDef.h"
#include "Log.h"

class NdkRender {
public:
    NdkRender();
    ~NdkRender();

    void init();
    void draw();
    void sizeChanged(int w, int h);

    void setupAssetManager(AAssetManager *pManager);

    void drawTriangle();
    void drawRectangle();
    void drawPoint();
    void drawLine();
    void drawPicture();

private:
    void loadTextureResources(AAssetManager *pManager);
    void loadShaderResources(AAssetManager *pManager);

private:
    float m_angle = 0.0f;
    GLuint m_texID[6];

    AAssetManager *m_pAssetManager;
};


#endif //OPENGLES_PROJECT_NDKRENDER_H
