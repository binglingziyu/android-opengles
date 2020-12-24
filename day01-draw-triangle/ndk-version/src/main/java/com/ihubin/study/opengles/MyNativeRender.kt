package com.ihubin.study.opengles

class MyNativeRender {

    companion object {
        init {
            System.loadLibrary("native-render")
        }
    }

    external fun native_Init()
    external fun native_UnInit()
    external fun native_OnSurfaceCreated()
    external fun native_OnSurfaceChanged(width: Int, height: Int)
    external fun native_OnDrawFrame()

}