//
// Created by BaiYang on 2025-12-22.
//

#ifndef OPENGLES_PROJECT_NDKFBO_H
#define OPENGLES_PROJECT_NDKFBO_H

#include "CommonDef.h"

class NdkFBO {
public:
    NdkFBO();
    ~NdkFBO();

    void create(int width, int height);
    void bind();
    void release();

    GLuint getTextureId();

private:
    GLuint m_fboId;
    GLuint m_renderBufferId;
    GLuint m_colorTxtureId;
};


#endif //OPENGLES_PROJECT_NDKFBO_H
