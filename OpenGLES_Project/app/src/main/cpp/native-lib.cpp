//
// Created by BaiYang on 2025-11-30.
//

#define LOG_TAG "GLRenderJNI"
#include <jni.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#include "Log.h"
#include "NdkRender.h"

NdkRender g_ndkRender;

#ifdef __cplusplus
extern "C" {
#endif

void n_glInit(JNIEnv *env, jobject thiz, jobject asset_manager) {
    LOGI("n_glInit called.");
    // 将 Java 传递过来的 AssetManager 转换为 C 层可用的 AAssetManager
    // 并将其保存为全局引用，注意在多线程环境下的处理
    AAssetManager *astManager  = AAssetManager_fromJava(env, asset_manager);
    if (astManager != nullptr) {
        g_ndkRender.setupAssetManager(astManager);
    }

    g_ndkRender.init();
}

void n_glSizeChanged(JNIEnv *env, jobject thiz, jint width, jint height) {
    LOGI("n_glSizeChanged called. Width: %d, Height: %d", width, height);
    g_ndkRender.sizeChanged(width, height);
}

void n_glDraw(JNIEnv *env, jobject thiz) {
    g_ndkRender.draw();
}


static JNINativeMethod g_methods[] = {
        {"n_glInit", "(Landroid/content/res/AssetManager;)V", (void *)n_glInit},
        {"n_glSizeChanged", "(II)V", (void *)n_glSizeChanged},
        {"n_glDraw", "()V", (void *)n_glDraw}
};

static int register_native_methods(JNIEnv* env, const char* class_name) {
    jclass clazz = env->FindClass(class_name);
    if (clazz == nullptr) {
        return JNI_FALSE;
    }
    // 获取 g_methods 数组的大小（即有多少个方法需要注册）
    int method_count = sizeof(g_methods) / sizeof(g_methods[0]);
    // 关键调用：一次性注册所有方法
    if (env->RegisterNatives(clazz, g_methods, method_count) < 0) {
        return JNI_FALSE;
    }
    return JNI_TRUE;
}

// 动态库被加载时的入口函数
JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved) {
    LOGI("JNI_OnLoad started.");
    JNIEnv* env = NULL;
    if (vm->GetEnv((void**)&env, JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }

    // Java类的全路径名，点号用斜杠代替
    const char* class_name = "com/example/opengles_project/GLRender";

    // 注册
    if (!register_native_methods(env, class_name)) {
        LOGE("Failed to register native methods.");
        return JNI_ERR;
    }

    LOGI("JNI_OnLoad finished. Native methods registered successfully.");
    return JNI_VERSION_1_6;
}

#ifdef __cplusplus
}
#endif