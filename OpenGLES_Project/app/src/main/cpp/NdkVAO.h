//
// Created by BaiYang on 2025-12-22.
//

#ifndef OPENGLES_PROJECT_NDKVAO_H
#define OPENGLES_PROJECT_NDKVAO_H

#include "CommonDef.h"

class NdkVAO {
public:
    NdkVAO();
    ~NdkVAO();

    void create();
    void bind();
    void release();

private:
    GLuint m_vaoId;
};

#endif //OPENGLES_PROJECT_NDKVAO_H
