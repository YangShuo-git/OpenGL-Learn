//
// Created by BaiYang on 2025-12-21.
//

#ifndef OPENGLES_PROJECT_NDKSHADER_H
#define OPENGLES_PROJECT_NDKSHADER_H

#include "CommonDef.h"

class NdkShader {

public:
    NdkShader();
    ~NdkShader();

    void bind();
    void release();

    void initShadersFromFile(AAssetManager*  pManager, const char* vShader, const char* fshader);

    void disableAttributeArray(const char *name);
    void enableAttributeArray(const char *name);
    void setAttributeBuffer(const char* name, GLenum type, const void *values, int tupleSize, int stride = 0);

    void setAttributeBuffer(int location,GLenum type, const void *values, int tupleSize, int stride = 0);
    void disableAttributeArray(int location);
    void enableAttributeArray(int location);

    void setUniformValue(const char* name, int iValue);
    void setUniformValue(const char* name, GLfloat fValue);
    void setUniformValue(const char* name, glm::vec3 vecValue);
    void setUniformValue(const char* name, glm::mat4 matValue);

private:
    int compileShader(AAssetManager*  m_pAssetManager,const char* sPath, GLint sType);

private:
    GLuint m_shaderProgram;
};


#endif //OPENGLES_PROJECT_NDKSHADER_H
