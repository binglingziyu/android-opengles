package com.ihubin.study.opengles

import android.opengl.GLSurfaceView
import android.util.Log
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

class MyGLRender internal constructor() : GLSurfaceView.Renderer {

    companion object {
        private const val TAG = "MyGLRender"
    }

    private val mNativeRender: MyNativeRender = MyNativeRender()

    override fun onSurfaceCreated(gl: GL10, config: EGLConfig) {
        mNativeRender.native_OnSurfaceCreated()
        Log.e(
            TAG,
            "onSurfaceCreated() called with: GL_VERSION = [" + gl.glGetString(GL10.GL_VERSION) + "]"
        )
    }

    override fun onSurfaceChanged(gl: GL10, width: Int, height: Int) {
        mNativeRender.native_OnSurfaceChanged(width, height)
    }

    override fun onDrawFrame(gl: GL10) {
        mNativeRender.native_OnDrawFrame()
    }

    fun init() {
        mNativeRender.native_Init()
    }

    fun unInit() {
        mNativeRender.native_UnInit()
    }


}