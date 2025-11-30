package com.example.opengles_project;

import android.content.Context;
import android.content.res.AssetManager;
import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class GLRender implements GLSurfaceView.Renderer {
    static {
        System.loadLibrary("GLRender");
    }

    private Context m_Ctx;

    GLRender(Context ctx) {
        m_Ctx = ctx;
    }

    @Override
    public void onSurfaceCreated(GL10 gl10, EGLConfig eglConfig) {
        AssetManager assetManager = m_Ctx.getAssets();
        n_glInit(assetManager);
    }

    @Override
    public void onSurfaceChanged(GL10 gl10, int width, int height) {
        n_glSizeChanged(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl10) {
        n_glDraw();
    }


    private native void n_glInit(AssetManager assetManager);
    private native void n_glSizeChanged(int width,int height);
    private native void n_glDraw();
}
