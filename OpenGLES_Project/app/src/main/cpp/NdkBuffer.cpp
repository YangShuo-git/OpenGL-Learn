//
// Created by BaiYang on 2025-12-13.
//

#include "NdkBuffer.h"
#include "Log.h"

NdkBuffer::NdkBuffer(NdkBuffer::Type type, NdkBuffer::UsagePattern usage)
        :m_bufferType(type), m_usage(usage), m_buffSize(0) {
}

NdkBuffer::~NdkBuffer() {
    glDeleteBuffers(1, &m_buffID);
}

void NdkBuffer::create() {
    glGenBuffers(1, &m_buffID);
}

void NdkBuffer::bind() {
    glBindBuffer(m_bufferType, m_buffID);
}

void NdkBuffer::release() {
    glBindBuffer(m_bufferType, 0);
}

void NdkBuffer::setBufferData(const GLvoid *data, GLsizeiptr size) {
    if (size > m_buffSize) {
        m_buffSize = size;
        glBufferData(m_bufferType, size, data, m_usage);
    } else {
        glBufferSubData(m_bufferType, 0, size, data);
    }
}
