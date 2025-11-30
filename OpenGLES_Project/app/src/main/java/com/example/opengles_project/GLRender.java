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
        n_initGL();

        n_readAssetFile(assetManager, "earth.png");
    }

    @Override
    public void onSurfaceChanged(GL10 gl10, int width, int height) {
        n_changeSizeGL(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl10) {
        n_drawGL();
    }


    private native void n_initGL();
    private native void n_drawGL();
    private native void n_changeSizeGL(int width,int height);
    private native int n_readAssetFile(AssetManager assetManager, String fileName);
}
