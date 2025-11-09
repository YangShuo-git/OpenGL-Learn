//
// Created by BaiYang on 2025-11-09.
//

#include "com_example_opengles_project_GLRender.h"

#include "Log.h"
#include "GLPrimitives.h"

#ifdef __cplusplus
extern "C" {
#endif

void Java_com_example_opengles_1project_GLRender_n_1initGL(JNIEnv *, jobject) {
    glClearColor(1.0,0.0,0.0,1.0);
    glClearDepthf(1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    LOGD("OpenGL init");
}

void Java_com_example_opengles_1project_GLRender_n_1drawGL(JNIEnv *, jobject){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    drawTriangle();
    drawRectangle();
}

void Java_com_example_opengles_1project_GLRender_n_1changeSizeGL(JNIEnv *, jobject, jint width, jint height){
    glViewport(0,0,width,height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // 正交投影
    glOrthof(-1,1,-1,1,0.1,1000.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    LOGD("OpenGL change size: %d, %d", width, height);
}

#ifdef __cplusplus
}
#endif
