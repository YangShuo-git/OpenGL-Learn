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

    void Bind();
    void Release();

    void InitShadersFromFile(AAssetManager*  pManager, const char* vShader,const char* fshader);

    void DisableAttributeArray(const char *name);
    void EnableAttributeArray(const char *name);
    void SetAttributeBuffer(const char* name,GLenum type, const void *values, int tupleSize, int stride = 0);

    void SetUniformValue(const char* name, int iValue);
    void SetUniformValue(const char* name, GLfloat fValue);
    void SetUniformValue(const char* name, glm::vec3 vecValue);
    void SetUniformValue(const char* name, glm::mat4 matValue);

private:
    int compileShader(AAssetManager*  m_pAssetManager,const char* sPath, GLint sType);
private:
    GLuint m_shaderProgram;
};


#endif //OPENGLES_PROJECT_NDKSHADER_H
