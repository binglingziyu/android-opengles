//
// Created by apple on 2020/12/24.
//
#include "util/LogUtil.h"
#include "jni.h"
#include "MyGLRenderContext.h"

#define NATIVE_RENDER_CLASS_NAME "com/ihubin/study/opengles/MyNativeRender"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Class:     com_ihubin_study_opengles_MyNativeRender
 * Method:    native_Init
 * Signature: ()V
 */
JNIEXPORT void JNICALL native_Init(JNIEnv *, jobject) {
	MyGLRenderContext::GetInstance();

}

/*
 * Class:     com_ihubin_study_opengles_MyNativeRender
 * Method:    native_UnInit
 * Signature: ()V
 */
JNIEXPORT void JNICALL native_UnInit(JNIEnv *, jobject) {
	MyGLRenderContext::DestroyInstance();
}

/*
 * Class:     com_ihubin_study_opengles_MyNativeRender
 * Method:    native_OnSurfaceCreated
 * Signature: ()V
 */
JNIEXPORT void JNICALL native_OnSurfaceCreated(JNIEnv *, jobject) {
    MyGLRenderContext::GetInstance()->OnSurfaceCreated();
}

/*
 * Class:     com_ihubin_study_opengles_MyNativeRender
 * Method:    native_OnSurfaceChanged
 * Signature: (II)V
 */
JNIEXPORT void JNICALL native_OnSurfaceChanged
        (JNIEnv *, jobject, jint width, jint height) {
    MyGLRenderContext::GetInstance()->OnSurfaceChanged(width, height);
}

/*
 * Class:     com_ihubin_study_opengles_MyNativeRender
 * Method:    native_OnDrawFrame
 * Signature: ()V
 */
JNIEXPORT void JNICALL native_OnDrawFrame(JNIEnv *, jobject) {
    MyGLRenderContext::GetInstance()->OnDrawFrame();
}


#ifdef __cplusplus
}
#endif

static JNINativeMethod g_RenderMethods[] = {
		{"native_Init",                      "()V",       (void *)(native_Init)},
		{"native_UnInit",                    "()V",       (void *)(native_UnInit)},
		{"native_OnSurfaceCreated",          "()V",       (void *)(native_OnSurfaceCreated)},
		{"native_OnSurfaceChanged",          "(II)V",     (void *)(native_OnSurfaceChanged)},
		{"native_OnDrawFrame",               "()V",       (void *)(native_OnDrawFrame)},
};


static int RegisterNativeMethods(JNIEnv *env, const char *className, JNINativeMethod *methods, int methodNum) {
	LOGCATE("RegisterNativeMethods");
	jclass clazz = env->FindClass(className);
	if (clazz == nullptr) {
		LOGCATE("RegisterNativeMethods fail. clazz == NULL");
		return JNI_FALSE;
	}
	if (env->RegisterNatives(clazz, methods, methodNum) < 0) {
		LOGCATE("RegisterNativeMethods fail");
		return JNI_FALSE;
	}
	return JNI_TRUE;
}

static void UnregisterNativeMethods(JNIEnv *env, const char *className) {
	LOGCATE("UnregisterNativeMethods");
	jclass clazz = env->FindClass(className);
	if (clazz == nullptr) {
		LOGCATE("UnregisterNativeMethods fail. clazz == NULL");
		return;
	}
    env->UnregisterNatives(clazz);
}

extern "C" jint JNI_OnLoad(JavaVM *jvm, void *p) {
	LOGCATE("===== JNI_OnLoad =====");
	jint jniRet = JNI_ERR;
	JNIEnv *env = nullptr;
	if (jvm->GetEnv((void **) (&env), JNI_VERSION_1_6) != JNI_OK) {
		return jniRet;
	}

	jint regRet = RegisterNativeMethods(env, NATIVE_RENDER_CLASS_NAME, g_RenderMethods,
										sizeof(g_RenderMethods) /
										sizeof(g_RenderMethods[0]));
	if (regRet != JNI_TRUE) {
		return JNI_ERR;
	}


	return JNI_VERSION_1_6;
}

extern "C" void JNI_OnUnload(JavaVM *jvm, void *p) {
	JNIEnv *env = nullptr;
	if (jvm->GetEnv((void **) (&env), JNI_VERSION_1_6) != JNI_OK) {
		return;
	}
	UnregisterNativeMethods(env, NATIVE_RENDER_CLASS_NAME);
}
