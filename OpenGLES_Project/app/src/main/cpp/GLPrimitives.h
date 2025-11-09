//
// Created by BaiYang on 2025-11-09.
//

#ifndef OPENGLES_PROJECT_GLPRIMITIVES_H
#define OPENGLES_PROJECT_GLPRIMITIVES_H

#include <GLES/gl.h>
#include <GLES2/gl2.h>

#ifdef __cplusplus
extern "C" {
#endif

struct  PriFloat7{
    float x;
    float y;
    float z;
    float r;
    float g;
    float b;
    float a;
};

struct  PriFloat3{
    float x;
    float y;
    float z;
};

void drawTriangle() {
    PriFloat7 vertexTriangle[] ={
            {0.5,0.1,-0.1,1.0,0.0,0.0,1.0},
            {0.5,0.8,-0.1,0.0,1.0,0.0,1.0},
            {-0.5,0.1,-0.1,0.0,0.0,1.0,1.0},

    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3,GL_FLOAT,sizeof(PriFloat7),vertexTriangle);
    glColorPointer(4, GL_FLOAT, sizeof(PriFloat7),&vertexTriangle[0].r);

    glDrawArrays(GL_TRIANGLES,0,3);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void drawRectangle() {
    PriFloat7 vertexTriangle[] ={
            {-0.5,-0.1,-0.1,1.0,0.0,0.0,1.0},
            {-0.5,-0.8,-0.1,0.0,1.0,0.0,1.0},
            {0.5,-0.1,-0.1,0.0,0.0,1.0,1.0},
            {0.5,-0.8,-0.1,1.0,0.0,1.0,1.0},
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3,GL_FLOAT,sizeof(PriFloat7),vertexTriangle);
    glColorPointer(4, GL_FLOAT, sizeof(PriFloat7),&vertexTriangle[0].r);

    glDrawArrays(GL_TRIANGLE_STRIP,0,4);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}


#ifdef __cplusplus
}
#endif

#endif //OPENGLES_PROJECT_GLPRIMITIVES_H
