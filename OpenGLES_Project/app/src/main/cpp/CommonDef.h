//
// Created by BaiYang on 2025-11-09.
//

#ifndef OPENGLES_PROJECT_COMMONDEF_H
#define OPENGLES_PROJECT_COMMONDEF_H

#include <GLES/gl.h>
#include <GLES2/gl2.h>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#include <assert.h>
#include <android/asset_manager_jni.h>
#include <android/asset_manager.h>

#include "Log.h"

#ifdef __cplusplus
extern "C" {
#endif

struct  PriFloat3{
    float x;
    float y;
    float z;
};

struct  PriFloat4{
    float r;
    float g;
    float b;
    float a;
};

struct  PriFloat5{
    float x;
    float y;
    float z;
    float u;
    float v;
};

struct  PriFloat7{
    float x;
    float y;
    float z;
    float r;
    float g;
    float b;
    float a;
};

#ifdef __cplusplus
}
#endif

template<typename T>
void safeDeletePtr(T* ptr)
{
    delete ptr;
    ptr = NULL;
}


#endif //OPENGLES_PROJECT_COMMONDEF_H
