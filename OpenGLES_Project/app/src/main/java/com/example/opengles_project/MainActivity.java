package com.example.opengles_project;

import android.content.res.AssetManager;
import android.opengl.GLSurfaceView;
import android.os.Bundle;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

public class MainActivity extends AppCompatActivity {

    private GLSurfaceView m_glSurfaceView;
    private GLRender m_render;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        m_render = new GLRender(this);
        m_glSurfaceView = new GLSurfaceView(this);
        m_glSurfaceView.setRenderer(m_render);

        //AssetManager assetManager = this.getAssets();
        //setContentView(R.layout.activity_main);
        setContentView(m_glSurfaceView);
    }
}