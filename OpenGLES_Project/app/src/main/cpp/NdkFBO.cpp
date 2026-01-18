//
// Created by BaiYang on 2025-12-22.
//

#include "NdkFBO.h"

//
// Created by chenchao on 2021/8/13.
//

#include "NdkFBO.h"

NdkFBO::NdkFBO()
{
}

NdkFBO::~NdkFBO()
{
    glDeleteTextures(1,&m_colorTxtureId);
}

void NdkFBO::create(int width, int height)
{
    // 创建并初始化颜色附件纹理
    glGenTextures(1,&m_colorTxtureId);
    glBindTexture(GL_TEXTURE_2D, m_colorTxtureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // 必须先为纹理分配存储空间，再将其附加到FBO
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,width,height,0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glBindTexture(GL_TEXTURE_2D,0);

    // 创建并初始化渲染缓冲对象（作为深度附件）
    glGenRenderbuffers(1, &m_renderBufferId);
    glBindRenderbuffer(GL_RENDERBUFFER, m_renderBufferId);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width,height);
    glBindFramebuffer(GL_FRAMEBUFFER,0);

    // 创建FBO并附加附件
    glGenFramebuffers(1, &m_fboId);
    glBindFramebuffer(GL_FRAMEBUFFER, m_fboId);

    // 附加颜色附件和深度附件
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colorTxtureId, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_renderBufferId);

    GLenum status = glCheckFramebufferStatus( GL_FRAMEBUFFER);
    if(status == GL_FRAMEBUFFER_COMPLETE) {
        LOGD("Framebuffer creation successful");
    } else {
        LOGE("Error creating framebuffer [status: %d]", status);
    }

    glBindRenderbuffer(GL_RENDERBUFFER,0);
}

void NdkFBO::bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER,m_fboId);
}

void NdkFBO::release()
{
    glBindFramebuffer(GL_FRAMEBUFFER,0);
}

GLuint NdkFBO::getTextureId()
{
    return m_colorTxtureId;
}