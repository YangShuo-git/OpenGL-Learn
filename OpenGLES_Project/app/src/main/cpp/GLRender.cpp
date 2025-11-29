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
    glClearColor(0.0,0.0,0.0,1.0);
    glClearDepthf(1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    LOGD("OpenGL init");
}

void Java_com_example_opengles_1project_GLRender_n_1drawGL(JNIEnv *, jobject){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    drawTriangle();
//    drawRectangle();
//    drawLine();
//    drawPoint();
}

void Java_com_example_opengles_1project_GLRender_n_1changeSizeGL(JNIEnv *, jobject, jint width, jint height){
    glViewport(0,0,width,height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // 正交投影 相当于摄像机  n是朝里，z是朝外，0.1和-0.1正在在一个平面  n<0.1的值都能拍摄到
    glOrthof(-1,1,-1,1,0.1,1000.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    LOGD("OpenGL change size: %d, %d", width, height);
}

#ifdef __cplusplus
}
#endif
