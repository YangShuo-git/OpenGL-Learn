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

    void createWithSize(int width, int height);
    void bind();
    void release();

    GLuint getTextureID();

private:
    GLuint m_fboId;
    GLuint m_renderBufferId;
    GLuint m_textureId;
};


#endif //OPENGLES_PROJECT_NDKFBO_H
