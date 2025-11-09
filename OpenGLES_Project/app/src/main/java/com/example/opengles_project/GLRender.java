package com.example.opengles_project;

import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class GLRender implements GLSurfaceView.Renderer {
    static {
        System.loadLibrary("GLRender");
    }

    @Override
    public void onSurfaceCreated(GL10 gl10, EGLConfig eglConfig) {
        n_initGL();
    }

    @Override
    public void onSurfaceChanged(GL10 gl10, int width, int height) {
        n_changeSizeGL(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl10) {
        n_drawGL();
    }


    private native  void n_initGL();
    private native  void n_drawGL();
    private native  void n_changeSizeGL(int width,int height);
}
