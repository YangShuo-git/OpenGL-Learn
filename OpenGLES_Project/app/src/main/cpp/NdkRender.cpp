//
// Created by BaiYang on 2025-11-30.
//
#define LOG_TAG "NdkRender"
#include <string>
#include <vector>

#include "NdkRender.h"

NdkRender::NdkRender():m_pAssetManager(nullptr) {
    m_pVAO = new NdkVAO();
    m_pVBO = new NdkBuffer(NdkBuffer::VertexBuffer,NdkBuffer::StaticDraw);
    m_pEBO = new NdkBuffer(NdkBuffer::IndexBuffer,NdkBuffer::StaticDraw);

    m_pShader = new NdkShader();

    m_pFBO  = new NdkFBO();
    m_pFVAO = new NdkVAO();
    m_pFVBO = new NdkBuffer(NdkBuffer::VertexBuffer,NdkBuffer::StaticDraw);
    m_pFEBO = new NdkBuffer(NdkBuffer::IndexBuffer,NdkBuffer::StaticDraw);
    m_fboShader = new NdkShader();
}

NdkRender::~NdkRender() {
    glDeleteTextures(6,m_texID);

    safeDeletePtr(m_pVBO);
    safeDeletePtr(m_pEBO);

    safeDeletePtr(m_pFVBO);
    safeDeletePtr(m_pFEBO);
}

void NdkRender::init() {
    LOGI("init");

    glClearColor(0.0,0.0,0.0,1.0);
    glClearDepthf(1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    if(m_pAssetManager != nullptr) {
        loadTextureResources(m_pAssetManager);
        loadShaderResources(m_pAssetManager);
    }

//    setupDrawingCube();
//    setupDrawingEffect();

    setupDrawingWithFBO();
    setupDrawingScreen();

#if 0
    // 2.0的使用方式
    PriFloat5 planVertices[] = {
        { -1.0f, -1.0f, 1.0f, 0, 0 },
        { -1.0f, 1.0f, 1.0f, 0, 1 },
        { 1.0f, -1.0f, 1.0f, 1, 0 },
        { 1.0f, 1.0f, 1.0f, 1, 1 },
    };

    const short cubeIndexs[]= {
        0, 1, 2,  2, 1, 3,
    };

    m_pVBO->create();
    m_pVBO->bind();
    m_pVBO->setBufferData(planVertices, sizeof(planVertices));
    m_pVBO->release();

    m_pEBO->create();
    m_pEBO->bind();
    m_pEBO->setBufferData(cubeIndexs, sizeof(cubeIndexs));
    m_pEBO->release();
#endif
}

void NdkRender::draw() {
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    drawTriangleByShader();
//    drawRect();
//    drawCube();
//    drawTransition();
//    drawEffect();

//    m_pFBO->bind();
//    drawTriangleByShader();
//    m_pFBO->release();
    drawToFBO();
    drawToScreen();

#if 0
    // 2.0的使用方式
    glLoadIdentity();

    drawTriangle();
    drawRectangle();
    drawPoint();
    drawLine();
    drawPicture();
#endif
}

void NdkRender::sizeChanged(int w, int h) {
    LOGI("sizeChanged: %d, %d", w, h);
    glViewport(0,0,w,h);

#if 0
    // 2.0的使用方式
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrthof(-1,1,-1,1,0.1,1000.0);
#endif
}

void NdkRender::setAssetManager(AAssetManager *pManager) {
    if(pManager == nullptr){
        return;
    }
    m_pAssetManager = pManager;
}

void NdkRender::loadTextureResources(AAssetManager *pManager) {
    const std::vector<std::string> imageFiles = {
        "earth.png",
        "mars.png",
        "girl.png",
        "dog.png",
        "moon.png",
        "leaf.png"
    };

    for(int i=0; i<imageFiles.size(); i++){
        NdkTexture glTexture;
        m_texID[i] = glTexture.createTextureFromFile(pManager,imageFiles[i].c_str());
    }
}

void NdkRender::loadShaderResources(AAssetManager *pManager) {
    //初始化
//    m_pShader->initShadersFromFile(pManager,"highlight_vert.glsl","highlight_frag.glsl");

//    m_pShader->initShadersFromFile(pManager,"mosaic_vert.glsl","mosaic_frag.glsl");
//    m_pShader->initShadersFromFile(pManager,"ripple_vert.glsl","ripple_frag.glsl");
//    m_pShader->initShadersFromFile(pManager,"fade_vert.glsl","fade_frag.glsl");
//    m_pShader->initShadersFromFile(pManager,"burn_vert.glsl","burn_frag.glsl");
//    m_pShader->initShadersFromFile(pManager,"transition_vert.glsl","transition_frag.glsl");

    // 为什么drawRect都可以使用这两个呢？
//    m_pShader->initShadersFromFile(pManager, "cube_vert.glsl", "cube_frag.glsl");
//    m_pShader->initShadersFromFile(pManager, "vertex.glsl", "fragment.glsl");

    m_fboShader->initShadersFromFile(pManager, "fbo_vert.glsl", "fbo_frag.glsl");
    m_pShader->initShadersFromFile(pManager, "cube_vert.glsl", "cube_frag.glsl");
}

void NdkRender::setupFBO() {
    int viewport[4] = {0};
    // 获取手机宽高
    glGetIntegerv(GL_VIEWPORT,viewport);
    int width = viewport[2];
    int height = viewport[3];

    LOGI("FBO viewport: %d, %d", viewport[2],viewport[3]);
    if (width>0 && height>0) {
        m_pFBO->create(900, 900);
    }
}

void NdkRender::setupDrawingEffect() {
    if(m_pShader == NULL){
        return;
    }

    const PriFloat5 planeVertexs[]  = {
        {  -1.0,-1.0, 0.0 ,  0.0, 0.0 },
        {  -1.0, 1.0, 0.0 ,  0.0, 1.0 },
        {  1.0, -1.0,  0.0 , 1.0, 0.0 },
        {  1.0, 1.0, 0.0 ,  1.0, 1.0 },
    };

    const short planeIndexs[]= {
        0, 1, 2,  1, 3, 2
    };

    m_pVAO->create();
    m_pVAO->bind();

    m_pVBO->create();
    m_pVBO->bind();
    m_pVBO->setBufferData(planeVertexs,sizeof(planeVertexs));

    m_pEBO->create();
    m_pEBO->bind();
    m_pEBO->setBufferData(planeIndexs,sizeof(planeIndexs));

    int offset = 0;
    m_pShader->setAttributeBuffer(0,GL_FLOAT, (void *)offset, 3, sizeof(PriFloat5));
    m_pShader->enableAttributeArray(0);

    offset += 3 * sizeof(float);
    m_pShader->setAttributeBuffer(1,GL_FLOAT, (void *)offset, 2, sizeof(PriFloat5));
    m_pShader->enableAttributeArray(1);

    m_pVAO->release();
    m_pVBO->release();
    m_pEBO->release();
}

void NdkRender::drawEffect() {
    m_nValue += 0.01f;
    m_angle  += 0.01f;

    glm::mat4x4  objectMat;
    glm::mat4x4  objectTransMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3));
    glm::mat4x4  objectRotMat = glm::rotate(glm::mat4(1.0f),m_angle,glm::vec3(1.0f, 1.0f, 1.0) );
    glm::mat4x4  objectScaleMat = glm::scale(glm::mat4(1.0f),glm::vec3(1.0f, 1.0f, 1.0) );

    glm::mat4 projMat = glm::perspective(glm::radians(60.0f), (float)9/(float)18, 0.1f, 1000.0f);
    objectMat = projMat* objectTransMat ;

    m_pShader->bind();

    m_pShader->setUniformValue("u_mat",objectMat);
    m_pShader->setUniformValue("iTime",m_nValue);

    //burn ripple fade等的shader没有该变量,但是仍然可以运行
    m_pShader->setUniformValue("iResolution",glm::vec2(1.0f,1.0f));

    m_pShader->setUniformValue("iChannel0",0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,m_texID[0]);

    m_pShader->setUniformValue("iChannel1",1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D,m_texID[1]);

    m_pShader->setUniformValue("iChannel2",2);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D,m_texID[2]);

    m_pVAO->bind();
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_SHORT,NULL);

    m_pShader->release();
    m_pVAO->release();
    glBindTexture(GL_TEXTURE_2D,0);
}

void NdkRender::drawTransition() {
    m_nValue += 0.005f;
    if(m_nValue > 1.0f){
        m_nValue = 0.0f;
    }

    m_angle += 0.01f;

    glm::mat4x4  objectMat;
    glm::mat4x4  objectTransMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3));
    glm::mat4x4  objectRotMat = glm::rotate(glm::mat4(1.0f),m_angle,glm::vec3(1.0f, 1.0f, 1.0) );
    glm::mat4x4  objectScaleMat = glm::scale(glm::mat4(1.0f),glm::vec3(1.0f, 1.0f, 1.0f) );

    glm::mat4 projMat = glm::perspective(glm::radians(60.0f), (float)9/(float)18, 0.1f, 1000.0f);
    objectMat = projMat* objectTransMat ;

    m_pShader->bind();

    //设置mvp矩阵
    m_pShader->setUniformValue("u_mat",objectMat);
    m_pShader->setUniformValue("uValue",m_nValue);

    //设置纹理
    m_pShader->setUniformValue("utexture0",0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,m_texID[0]);
    m_pShader->setUniformValue("utexture1",1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D,m_texID[1]);

    m_pVAO->bind();

    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_SHORT,NULL);

    m_pShader->release();
    m_pVAO->release();
    glBindTexture(GL_TEXTURE_2D,0);
}

void NdkRender::setupDrawingCube() {
    if(m_pShader == NULL){
        return;
    }

    // 顶点坐标 + 纹理坐标
    const PriFloat5 cubeVertexs[]  = {
        {-1.0,-1.0, 1.0 ,  0.0, 0.0 },
        {-1.0, 1.0, 1.0 ,  0.0, 1.0 },
        {1.0, -1.0,  1.0 , 1.0, 0.0 },
        {1.0, 1.0, 1.0 ,  1.0, 1.0 },

        {1.0,-1.0, -1.0,   0,  0  },
        {1.0, 1.0, -1.0,   0,  1  },
        {-1.0,-1.0, -1.0,   1,  0 },
        {-1.0, 1.0, -1.0,   1,  1 },

        {-1.0, -1.0, -1.0,  0,  0 },
        {-1.0, 1.0, -1.0,   0,  1 },
        {-1.0, -1.0,  1.0,  1,  0 },
        {-1.0, 1.0, 1.0,    1,  1 },

        {1.0,-1.0,  1.0,    0,  0 },
        {1.0, 1.0,  1.0,    0,  1 },
        {1.0, -1.0,  -1.0,  1,  0 },
        {1.0, 1.0, -1.0,    1,  1 },

        {-1.0, 1.0,  1.0,   0,  0 },
        {-1.0, 1.0,  -1.0,  0,  1 },
        {1.0, 1.0, 1.0,     1,  0 },
        {1.0, 1.0, -1.0,    1,  1 },

        {-1.0, -1.0, -1.0,  0,  0 },
        {-1.0, -1.0, 1.0,   0,  1 },
        {1.0, -1.0, -1.0,   1,  0 },
        {1.0, -1.0, 1.0,    1,  1 }
    };

    const short cubeIndexs[]= {
        0, 1, 2,  2, 1, 3,
        4, 5, 6,  6, 5, 7,
        8, 9, 10, 10, 9,11,
        12,13,14, 14,13,15,
        16,17,18, 18,17,19,
        20,21,22, 22,21,23,
    };

    m_pVAO->create();
    m_pVAO->bind();

    m_pVBO->create();
    m_pVBO->bind();
    m_pVBO->setBufferData(cubeVertexs,sizeof(cubeVertexs));

    m_pEBO->create();
    m_pEBO->bind();
    m_pEBO->setBufferData(cubeIndexs,sizeof(cubeIndexs));

    int offset = 0;
    m_pShader->setAttributeBuffer(0,GL_FLOAT, (void *)offset, 3, sizeof(PriFloat5));
    m_pShader->enableAttributeArray(0);

    offset += 3 * sizeof(float);
    m_pShader->setAttributeBuffer(1,GL_FLOAT, (void *)offset, 2, sizeof(PriFloat5));
    m_pShader->enableAttributeArray(1);

    m_pVAO->release();
    m_pVBO->release();
    m_pEBO->release();
}

void NdkRender::drawCube() {
    m_angle += 0.01f;

    glm::mat4x4  objectMat;
    glm::mat4x4  objectTransMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3));
    glm::mat4x4  objectRotMat = glm::rotate(glm::mat4(1.0f),m_angle,glm::vec3(1.0f, 1.0f, 1.0) );
    glm::mat4x4  objectScaleMat = glm::scale(glm::mat4(1.0f),glm::vec3(0.5f, 0.5f, 0.5f) );

    glm::mat4 projMat = glm::perspective(glm::radians(60.0f), (float)9/(float)18, 0.1f, 1000.0f);
    objectMat = projMat* objectTransMat * objectScaleMat* objectRotMat ;

    m_pShader->bind();
    m_pShader->setUniformValue("u_mat",objectMat);

    m_pVAO->bind();

    for(int i=0; i<6; i++){
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,m_texID[i]);

        // 将纹理资源m_texID[i]绘制到对应的纹理坐标中
        int offset = i * 6 * sizeof(unsigned short);
        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_SHORT,(void *)offset);

        glBindTexture(GL_TEXTURE_2D,0);
    }

    m_pShader->release();
    m_pVAO->release();
}

void NdkRender::setupDrawingRect() {
    // 顶点坐标 + 颜色
    PriFloat7 rectVert[] = {
        {-0.5,   -0.5,  0,  1,  0,  0,1.0},
        {-0.5,   0.5,   0,  0,  1,  0,1.0},
        {0.5,    -0.5,  0,  0,  0,  1,1.0},
        {0.5,    0.5,   0,  1,  1,  0,1.0},
    };

    unsigned short rectIndex[] = {
        0,1,2,
        1,3,2
    };

    m_pVAO->create();
    m_pVAO->bind();

    m_pVBO->create();
    m_pVBO->bind();
    m_pVBO->setBufferData(rectVert,sizeof(rectVert));

    m_pEBO->create();
    m_pEBO->bind();
    m_pEBO->setBufferData(rectIndex,sizeof(rectIndex));

    int offset = 0;
    m_pShader->setAttributeBuffer(0,GL_FLOAT, (void *)offset, 3, sizeof(PriFloat7));
    m_pShader->enableAttributeArray(0);

    offset += 3 * sizeof(float);
    m_pShader->setAttributeBuffer(1,GL_FLOAT, (void *)offset, 4, sizeof(PriFloat7));
    m_pShader->enableAttributeArray(1);

    m_pVAO->release();
    // 此时EBO的绑定已记录在VAO中，下面解绑EBO是安全的。
    // 后续在绘制时，只需绑定VAO，其内部记录的EBO状态会自动恢复
    m_pVBO->release();
    m_pEBO->release();
}

void NdkRender::drawRect() {
    glm::mat4x4  objectMat;
    glm::mat4x4  objectTransMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3));
    glm::mat4x4  objectRotMat = glm::rotate(glm::mat4(1.0f),m_angle,glm::vec3(1.0f, 1.0f, 1.0) );
    glm::mat4x4  objectScaleMat = glm::scale(glm::mat4(1.0f),glm::vec3(0.5f, 0.5f, 0.5f) );

    glm::mat4 projMat = glm::perspective(glm::radians(60.0f), (float)9/(float)18, 0.1f, 1000.0f);
    objectMat = projMat* objectTransMat * objectScaleMat* objectRotMat ;

    m_pShader->bind();
    m_pShader->setUniformValue("u_mat",objectMat);

    m_pVAO->bind();

    // 第四个参数indices在传统意义上是一个指针，指向CPU内存中索引数组
    // 传递 NULL：说明索引数据不在CPU中，而是在当前绑定的 GL_ELEMENT_ARRAY_BUFFER 缓冲区里，并且从该缓冲区的起始位置（偏移量0）开始读取
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_SHORT,NULL);

    m_pShader->release();
    m_pVAO->release();
}

void NdkRender::drawTriangleByShader() {
    PriFloat7 triangleVert[] ={
        {0,       0.5,    -1,  1,  0,  0,1.0},
        {-0.5,   -0.5,    -1,  0,  1,  0,1.0},
        {0.5,    -0.5,    -1,  0,  0,  1,1.0},
    };

    m_angle += 0.01f;

    glm::mat4x4 cubeMat;
    glm::mat4x4 cubeTransMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3));
    glm::mat4x4 cubeRotMat = glm::rotate(glm::mat4(1.0f),m_angle,glm::vec3(1.0f, 1.0f, 1.0) );
    glm::mat4x4 cubeScaleMat = glm::scale(glm::mat4(1.0f),glm::vec3(0.3f, 0.2f, 0.3) );

    glm::mat4 projMat = glm::perspective(glm::radians(60.0f), (float)9/(float)18, 0.1f, 1000.0f);
    cubeMat = projMat* cubeTransMat ;

    m_pShader->bind();
    m_pShader->setUniformValue("u_mat", cubeMat);

    // 未使用VBO、VAO
    // 每次draw之前，都要将顶点数据从cpu拷贝到gpu，浪费性能
    m_pShader->enableAttributeArray("a_position");
    m_pShader->enableAttributeArray("a_color");
    m_pShader->setAttributeBuffer("a_position",GL_FLOAT,triangleVert,3,sizeof(PriFloat7));
    m_pShader->setAttributeBuffer("a_color",GL_FLOAT,&triangleVert[0].r,4,sizeof(PriFloat7));

    glDrawArrays(GL_TRIANGLES,0,3);

    m_pShader->disableAttributeArray("a_position");
    m_pShader->disableAttributeArray("a_color");

    m_pShader->release();
}

void NdkRender::setupDrawingWithFBO() {
    setupFBO();
    if(m_fboShader == NULL){
        return;
    }

    const PriFloat5 vertexs[]  = {
        {-1.0,-1.0,1.0 , 0.0, 0.0 },
        {-1.0,1.0, 1.0 , 0.0, 1.0 },
        {1.0, -1.0,1.0 , 1.0, 0.0 },
        {1.0, 1.0, 1.0 , 1.0, 1.0 },
    };

    const short indexs[]= {
        0, 1, 2,
        2, 1, 3,
    };

    m_pFVAO->create();
    m_pFVAO->bind();

    m_pFVBO->create();
    m_pFVBO->bind();
    m_pFVBO->setBufferData(vertexs,sizeof(vertexs));

    m_pFEBO->create();
    m_pFEBO->bind();
    m_pFEBO->setBufferData(indexs,sizeof(indexs));

    int offset = 0;
    m_fboShader->setAttributeBuffer(0, GL_FLOAT, (void *)offset, 3, sizeof(PriFloat5));
    m_fboShader->enableAttributeArray(0);

    offset += 3 * sizeof(float);
    m_fboShader->setAttributeBuffer(1, GL_FLOAT, (void *)offset, 2, sizeof(PriFloat5));
    m_fboShader->enableAttributeArray(1);

    m_pFVAO->release();
    m_pFVBO->release();
    m_pFEBO->release();
}

void NdkRender::setupDrawingScreen() {
    const PriFloat5 vertexs[]  = {
            {-1.0,-1.0,1.0 , 0.0, 0.0 },
            {-1.0,1.0, 1.0 , 0.0, 1.0 },
            {1.0, -1.0,1.0 , 1.0, 0.0 },
            {1.0, 1.0, 1.0 , 1.0, 1.0 },
    };

    const short indexs[]= {
            0, 1, 2,
            2, 1, 3,
    };

    m_pVAO->create();
    m_pVAO->bind();

    m_pVBO->create();
    m_pVBO->bind();
    m_pVBO->setBufferData(vertexs,sizeof(vertexs));

    m_pEBO->create();
    m_pEBO->bind();
    m_pEBO->setBufferData(indexs,sizeof(indexs));

    int offset = 0;
    m_pShader->setAttributeBuffer(0,GL_FLOAT, (void *)offset, 3, sizeof(PriFloat5));
    m_pShader->enableAttributeArray(0);

    offset += 3 * sizeof(float);
    m_pShader->setAttributeBuffer(1,GL_FLOAT, (void *)offset, 2, sizeof(PriFloat5));
    m_pShader->enableAttributeArray(1);

    m_pVAO->release();
    m_pVBO->release();
    m_pEBO->release();
}

void NdkRender::drawToFBO() {
    m_pFBO->bind();

    glViewport(0,0,900,900);
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_angle += 0.00f;

    glm::mat4x4  objectMat;
    glm::mat4x4  objectTransMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
    glm::mat4x4  objectRotMat = glm::rotate(glm::mat4(1.0f),m_angle,glm::vec3(1.0f, 1.0f, 1.0) );
    glm::mat4x4  objectScaleMat = glm::scale(glm::mat4(1.0f),glm::vec3(1.0f, 1.0f, 1.0f) );

    float aspectRatio = 900.0f / 900.0f;
    glm::mat4 projMat = glm::perspective(glm::radians(60.0f), aspectRatio, 0.1f, 1000.0f);
    objectMat = projMat* objectTransMat * objectRotMat * objectScaleMat;

    m_pFVAO->bind();
    m_fboShader->bind();
    m_fboShader->setUniformValue("ufbotexture", 0);
    m_fboShader->setUniformValue("u_mat", objectMat);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texID[3]);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_SHORT,NULL);
    glBindTexture(GL_TEXTURE_2D,0);

    m_fboShader->release();
    m_pFVAO->release();
    m_pFBO->release();
}

void NdkRender::drawToScreen() {
    glViewport(0,0,1080,2320);
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_angle += 0.00f;

    glm::mat4x4  objectMat;
    glm::mat4x4  objectTransMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
    glm::mat4x4  objectRotMat = glm::rotate(glm::mat4(1.0f),m_angle,glm::vec3(1.0f, 1.0f, 1.0) );
    glm::mat4x4  objectScaleMat = glm::scale(glm::mat4(1.0f),glm::vec3(0.5f, 0.5f, 0.5f) );

    glm::mat4 projMat = glm::perspective(glm::radians(60.0f), (float)9/(float)18, 0.1f, 1000.0f);
    objectMat = projMat* objectTransMat * objectScaleMat* objectRotMat ;

    m_pVAO->bind();
    m_pShader->bind();
    m_pShader->setUniformValue("u_mat", objectMat);
    m_pShader->setUniformValue("utexture", 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_pFBO->getTextureId());
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_SHORT,NULL);
    glBindTexture(GL_TEXTURE_2D,0);

    m_pShader->release();
    m_pVAO->release();
}


// 2.0的使用方式
#if 0
void NdkRender::drawPicture() {
    m_pVBO->bind();

    //启用顶点数组功能，否则glVertexPointer设置无效
    //启用纹理坐标数组功能，否则glTexCoordPointer设置无效
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    //顶点位置从结构体开始位置（偏移0字节）开始
    //纹理坐标从偏移12字节（3个float × 4字节）开始
    float* vertexAddr = (float*)0;
    float* uvAddr = (float*)(3 * sizeof(float));

    glVertexPointer(3,GL_FLOAT,sizeof(PriFloat5),vertexAddr);
    glTexCoordPointer(2,GL_FLOAT,sizeof(PriFloat5),uvAddr);

    glm::mat4x4  cubeMat;
    glm::mat4x4  cubeTransMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -0.5));
    glm::mat4x4  cubeRotMat   = glm::rotate(glm::mat4(1.0f),m_angle,glm::vec3(0.5f, 0.5f, 1.0) );
    glm::mat4x4  cubeScaleMat = glm::scale(glm::mat4(1.0f),glm::vec3(0.5f, 0.3f, 0.1) );
    cubeMat = cubeTransMat * cubeRotMat * cubeScaleMat;
    glLoadMatrixf(glm::value_ptr(cubeMat));

    m_pEBO->bind();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,m_texID[0]);

    const short* indices =(const short *) (0*6*sizeof(short));
    glDrawElements(GL_TRIANGLES, 6,  GL_UNSIGNED_SHORT, indices);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    m_pVBO->release();
    m_pEBO->release();
}

void NdkRender::drawTriangle() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    PriFloat7 vertexTriangle[] ={
            {0.5,0.1,-0.1,1.0,0.0,0.0,1.0},
            {0.5,0.5,-0.1,0.0,1.0,0.0,1.0},
            {-0.5,0.1,-0.1,0.0,0.0,1.0,1.0},
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3,GL_FLOAT,sizeof(PriFloat7),vertexTriangle);

    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(4, GL_FLOAT, sizeof(PriFloat7),&vertexTriangle[0].r);

    m_angle += 0.01f; //旋转速度

    glm::mat4x4  cubeMat;
    glm::mat4x4  cubeTransMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -0.5));           //平移
    glm::mat4x4  cubeRotMat   = glm::rotate(glm::mat4(1.0f),m_angle,glm::vec3(0.5f, 0.5f, 1.0) ); //旋转
    glm::mat4x4  cubeScaleMat = glm::scale(glm::mat4(1.0f),glm::vec3(0.5f, 0.4f, 0.1) );                //缩放
    cubeMat = cubeTransMat * cubeRotMat * cubeScaleMat;

    glLoadMatrixf(glm::value_ptr(cubeMat));

    glDrawArrays(GL_TRIANGLES,0,3);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void NdkRender::drawRectangle() {
    PriFloat7 vertexTriangle[] ={
            {-0.5,-0.1,-0.1,1.0,0.0,0.0,1.0},
            {-0.5,-0.8,-0.1,0.0,1.0,0.0,1.0},
            {0.5,-0.1,-0.1,0.0,0.0,1.0,1.0},
            {0.5,-0.8,-0.1,1.0,0.0,1.0,1.0},
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3,GL_FLOAT,sizeof(PriFloat7),vertexTriangle);

    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(4, GL_FLOAT, sizeof(PriFloat7),&vertexTriangle[0].r);

    glDrawArrays(GL_TRIANGLE_STRIP,0,4);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void NdkRender::drawPoint() {
    PriFloat3 vertexTriangle[] ={
            {-0.5,-0.5,-0.1},
            {-0.5,0.5,-0.1},
            {0.5,-0.5,-0.1},
            {0.5,0.5,-0.1},
    };

    glColor4f(1.0, 1.0, 1.0, 1.0);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3,GL_FLOAT,sizeof(PriFloat3),vertexTriangle);

    glPointSize(20);
    glEnable(GL_POINT_SMOOTH);  //不使用smooth，会画出正方形
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

    glDrawArrays(GL_POINTS,0,4);

    glDisableClientState(GL_VERTEX_ARRAY);
}

void NdkRender::drawLine() {
    PriFloat3 vertexTriangle[] ={
            {-0.5,-0.5,-0.1},
            {-0.5,0.5,-0.1},
            {0.5,-0.5,-0.1},
            {0.5,0.5,-0.1},
    };

    glColor4f(1.0, 1.0, 1.0, 1.0);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3,GL_FLOAT,sizeof(PriFloat3),vertexTriangle);

    glLineWidth(4);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

    glDrawArrays(GL_LINE_LOOP,0,4);

    glDisableClientState(GL_VERTEX_ARRAY);
}
#endif
