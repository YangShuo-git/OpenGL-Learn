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
//
//void drawTriangle() {
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//
//    PriFloat7 vertexTriangle[] ={
//            {0.5,0.1,-0.1,1.0,0.0,0.0,1.0},
//            {0.5,0.5,-0.1,0.0,1.0,0.0,1.0},
//            {-0.5,0.1,-0.1,0.0,0.0,1.0,1.0},
//    };
//
//    glEnableClientState(GL_VERTEX_ARRAY);
//    glVertexPointer(3,GL_FLOAT,sizeof(PriFloat7),vertexTriangle);
//
//    glEnableClientState(GL_COLOR_ARRAY);
//    glColorPointer(4, GL_FLOAT, sizeof(PriFloat7),&vertexTriangle[0].r);
//
//    g_angle += 0.01f; //旋转速度
//
//    glm::mat4x4  cubeMat;
//    glm::mat4x4  cubeTransMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -0.5));           //平移
//    glm::mat4x4  cubeRotMat   = glm::rotate(glm::mat4(1.0f),g_angle,glm::vec3(0.5f, 0.5f, 1.0) ); //旋转
//    glm::mat4x4  cubeScaleMat = glm::scale(glm::mat4(1.0f),glm::vec3(0.5f, 0.4f, 0.1) );                //缩放
//    cubeMat = cubeTransMat * cubeRotMat * cubeScaleMat;
//
//    glLoadMatrixf(glm::value_ptr(cubeMat));
//
//    glDrawArrays(GL_TRIANGLES,0,3);
//
//    glDisableClientState(GL_VERTEX_ARRAY);
//    glDisableClientState(GL_COLOR_ARRAY);
//}
//
//void drawRectangle() {
//    PriFloat7 vertexTriangle[] ={
//            {-0.5,-0.1,-0.1,1.0,0.0,0.0,1.0},
//            {-0.5,-0.8,-0.1,0.0,1.0,0.0,1.0},
//            {0.5,-0.1,-0.1,0.0,0.0,1.0,1.0},
//            {0.5,-0.8,-0.1,1.0,0.0,1.0,1.0},
//    };
//
//    glEnableClientState(GL_VERTEX_ARRAY);
//    glVertexPointer(3,GL_FLOAT,sizeof(PriFloat7),vertexTriangle);
//
//    glEnableClientState(GL_COLOR_ARRAY);
//    glColorPointer(4, GL_FLOAT, sizeof(PriFloat7),&vertexTriangle[0].r);
//
//    glDrawArrays(GL_TRIANGLE_STRIP,0,4);
//
//    glDisableClientState(GL_VERTEX_ARRAY);
//    glDisableClientState(GL_COLOR_ARRAY);
//}
//
//void drawLine() {
//    PriFloat3 vertexTriangle[] ={
//            {-0.5,-0.5,-0.1},
//            {-0.5,0.5,-0.1},
//            {0.5,-0.5,-0.1},
//            {0.5,0.5,-0.1},
//    };
//
//    glColor4f(1.0, 1.0, 1.0, 1.0);
//    glEnableClientState(GL_VERTEX_ARRAY);
//    glVertexPointer(3,GL_FLOAT,sizeof(PriFloat3),vertexTriangle);
//
//    glLineWidth(4);
//    glEnable(GL_LINE_SMOOTH);
//    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
//
//    glDrawArrays(GL_LINE_LOOP,0,4);
//
//    glDisableClientState(GL_VERTEX_ARRAY);
//}
//
//void drawPoint() {
//    PriFloat3 vertexTriangle[] ={
//            {-0.5,-0.5,-0.1},
//            {-0.5,0.5,-0.1},
//            {0.5,-0.5,-0.1},
//            {0.5,0.5,-0.1},
//    };
//
//    glColor4f(1.0, 1.0, 1.0, 1.0);
//    glEnableClientState(GL_VERTEX_ARRAY);
//    glVertexPointer(3,GL_FLOAT,sizeof(PriFloat3),vertexTriangle);
//
//    glPointSize(20);
//    glEnable(GL_POINT_SMOOTH);  //不使用smooth，会画出正方形
//    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
//
//    glDrawArrays(GL_POINTS,0,4);
//
//    glDisableClientState(GL_VERTEX_ARRAY);
//}
//
//void drawPicture() {
//    PriFloat5 planVertices[] =
//            {
//                    { -1.0f, -1.0f, 1.0f,    0,  0 },
//                    {  -1.0f,1.0f, 1.0f,   0,  1 },
//                    {  1.0f,-1.0f, 1.0f,    1,  0 },
//                    {  1.0f, 1.0f, 1.0f,    1,  1 },
//            };
//
//    glBindTexture(GL_TEXTURE_2D, g_texID);
//
//    glEnableClientState(GL_VERTEX_ARRAY);
//    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
//    glVertexPointer(3,GL_FLOAT,sizeof(PriFloat5),planVertices);
//    glTexCoordPointer(2,GL_FLOAT,sizeof(PriFloat5),&planVertices[0].u);
//
//    glm::mat4x4  cubeMat;
//    glm::mat4x4  cubeTransMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -0.5));
//    glm::mat4x4  cubeRotMat   = glm::rotate(glm::mat4(1.0f),g_angle,glm::vec3(0.5f, 0.5f, 1.0) );
//    glm::mat4x4  cubeScaleMat = glm::scale(glm::mat4(1.0f),glm::vec3(0.5f, 0.3f, 0.1) );
//    cubeMat = cubeTransMat * cubeRotMat * cubeScaleMat;
//    glLoadMatrixf(glm::value_ptr(cubeMat));
//
//    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
//
//    glDisableClientState(GL_VERTEX_ARRAY);
//    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
//}

#ifdef __cplusplus
}
#endif

#endif //OPENGLES_PROJECT_COMMONDEF_H
