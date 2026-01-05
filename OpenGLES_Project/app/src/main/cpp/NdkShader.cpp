//
// Created by BaiYang on 2025-12-21.
//

#define LOG_TAG "NdkShader"

#include "NdkShader.h"

NdkShader::NdkShader()
{
    m_shaderProgram = 0;
}

NdkShader::~NdkShader()
{
}

void NdkShader::initShadersFromFile(AAssetManager* pManager, const char* vShader, const char* fshader)
{
    GLuint vertexId = 0;
    GLuint fragId = 0;

    vertexId = compileShader(pManager, vShader , GL_VERTEX_SHADER);
    fragId   = compileShader(pManager, fshader , GL_FRAGMENT_SHADER);

    char message[512];
    int  status = 0;

    m_shaderProgram = glCreateProgram();
    if (vertexId != -1) {
        glAttachShader(m_shaderProgram, vertexId);
    }
    if (fragId != -1) {
        glAttachShader(m_shaderProgram, fragId);
    }

    glLinkProgram(m_shaderProgram);

    glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &status);
    if (!status) {
        glGetProgramInfoLog(m_shaderProgram, 512, NULL, message);
        LOGE("get shaderProgram failed: %s", message);
    }

    LOGI("shaderProgram sucess!\n");

    glDeleteShader(vertexId);
    glDeleteShader(fragId);
}

int NdkShader::compileShader(AAssetManager*  pManager,const char* fName, GLint sType)
{
    AAsset* file = AAssetManager_open(pManager,fName, AASSET_MODE_BUFFER);
    size_t shaderSize = AAsset_getLength(file);

    char* sContentBuff = (char*)malloc(shaderSize);
    AAsset_read(file, sContentBuff, shaderSize);
    LOGD("SHADERS: %s",sContentBuff);
    unsigned int shaderID = 0;
    char         message[512] = {0};
    int          status = 0;

    shaderID = glCreateShader(sType);
    glShaderSource(shaderID, 1, &sContentBuff, (const GLint *)&shaderSize);
    glCompileShader(shaderID);

    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);
    if (!status) {
        glGetShaderInfoLog(shaderID, 512, NULL, message);
        LOGF("Compile Shader Status failed: %s",message);
    }

    if(sContentBuff != NULL) {
        free(sContentBuff);
        sContentBuff = NULL;
    }

    AAsset_close(file);
    return shaderID;
}

void NdkShader::bind()
{
    glUseProgram(m_shaderProgram);
}

void NdkShader::release()
{
    glUseProgram(0);
}

void NdkShader::setUniformValue(const char* name, int iValue)
{
    glUniform1i(glGetUniformLocation(m_shaderProgram, name), iValue);
}

void NdkShader::setUniformValue(const char* name, GLfloat fValue)
{
    glUniform1f(glGetUniformLocation(m_shaderProgram, name), fValue);
}

void NdkShader::setUniformValue(const char* name, glm::vec2 vec2Value)
{
    glUniform2fv(glGetUniformLocation(m_shaderProgram, name), 1, (const GLfloat *)glm::value_ptr(vec2Value));
}

void NdkShader::setUniformValue(const char* name, glm::vec3 vecValue)
{
    glUniform3fv(glGetUniformLocation(m_shaderProgram, name), 1, glm::value_ptr(vecValue));
}

void NdkShader::setUniformValue(const char* name, glm::mat4 matValue)
{
    glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram, name) , 1 , GL_FALSE , glm::value_ptr(matValue));
}

void NdkShader::enableAttributeArray(const char *name)
{
    GLuint location = glGetAttribLocation(m_shaderProgram, name);
    glEnableVertexAttribArray(location);
}

void NdkShader::disableAttributeArray(const char *name)
{
    GLuint location = glGetAttribLocation(m_shaderProgram, name);
    glDisableVertexAttribArray(location);
}

void NdkShader::setAttributeBuffer(const char* name, GLenum type, const void *values, int tupleSize, int stride)
{
    GLuint location = glGetAttribLocation(m_shaderProgram, name);
    glVertexAttribPointer(location,tupleSize,type,GL_FALSE,stride,values);
}

void NdkShader::setAttributeBuffer(int location, GLenum type, const void *values, int tupleSize, int stride )
{
    glVertexAttribPointer(location,tupleSize, type,GL_FALSE, stride,values);
}

void NdkShader::enableAttributeArray(int location)
{
    glEnableVertexAttribArray(location);
}

void NdkShader::disableAttributeArray(int location)
{
    glDisableVertexAttribArray(location);
}