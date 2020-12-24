package com.ihubin.study.opengles

import android.app.ActivityManager
import android.content.Context
import android.opengl.GLSurfaceView
import android.os.Bundle
import android.util.Log
import androidx.appcompat.app.AppCompatActivity


class MainActivity : AppCompatActivity() {

    companion object {
        const val CONTEXT_CLIENT_VERSION = 3
    }

    private var mGLSurfaceView: GLSurfaceView? = null

    private val mGLRender = MyGLRender()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        mGLSurfaceView =  GLSurfaceView(this)

        if ( detectOpenGLES30()) {
            // Tell the surface view we want to create an OpenGL ES 3.0-compatible
            // context, and set an OpenGL ES 3.0-compatible renderer.
            mGLSurfaceView?.setEGLContextClientVersion(CONTEXT_CLIENT_VERSION)
            mGLRender.init()
            mGLSurfaceView?.setRenderer(mGLRender)
        } else {
            Log.e("HelloTriangle", "OpenGL ES 3.0 not supported on device.  Exiting...")
            finish()
        }

        setContentView(mGLSurfaceView)
    }

    private fun detectOpenGLES30(): Boolean {
        val am = getSystemService(Context.ACTIVITY_SERVICE) as ActivityManager
        val info = am.deviceConfigurationInfo
        return info.reqGlEsVersion >= 0x30000
    }

    override fun onResume() {
        // Ideally a game should implement onResume() and onPause()
        // to take appropriate action when the activity looses focus
        super.onResume()
        // mGLSurfaceView?.onResume()
    }

    override fun onPause() {
        // Ideally a game should implement onResume() and onPause()
        // to take appropriate action when the activity looses focus
        super.onPause()
        // mGLSurfaceView?.onPause()
    }

    override fun onDestroy() {
        super.onDestroy()
        mGLRender.unInit()
    }

}