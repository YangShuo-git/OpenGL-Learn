//
// Created by BaiYang on 2025-12-22.
//

#include "NdkVAO.h"

NdkVAO::NdkVAO() {

}

NdkVAO::~NdkVAO() {
    glDeleteVertexArrays(1,&m_vaoId);
}

void NdkVAO::create() {
    //3.0才生效
    glGenVertexArrays(1,&m_vaoId);
}

void NdkVAO::bind() {
    glBindVertexArray(m_vaoId);
}

void NdkVAO::release() {
    glBindVertexArray(0);
}
