//
// Created by BaiYang on 2025-11-09.
//

#ifndef OPENGLES_PROJECT_LOG_H
#define OPENGLES_PROJECT_LOG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <android/log.h>

#ifndef LOG_TAG
#define LOG_TAG "native"
#endif

#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define LOGF(...)  __android_log_print(ANDROID_LOG_FATAL,LOG_TAG,__VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif //OPENGLES_PROJECT_LOG_H
