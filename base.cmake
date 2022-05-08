
set(TUT_PRO "HelloPVR")
IF (WIN32)
    set(PVR_SDK_DIRECTORY "D:/PVRTools/Native_SDK-R21.2-v5.8")
    set(PVR_SDK_INC "${PVR_SDK_DIRECTORY}/framework"
                    "${PVR_SDK_DIRECTORY}/include"
                    "${PVR_SDK_DIRECTORY}/build/external/glm/src"
                    )
    set(PVR_SDK_LIB "${PVR_SDK_DIRECTORY}/build/framework/PVRCore/Debug/PVRCore.lib"
                    "${PVR_SDK_DIRECTORY}/build/framework/PVRShell/Debug/PVRShell.lib"
                    "${PVR_SDK_DIRECTORY}/build/framework/PVRAssets/Debug/PVRAssets.lib"
                    "${PVR_SDK_DIRECTORY}/build/framework/PVRUtils/OpenGLES/Debug/PVRUtilsGles.lib"
     )
ELSEIF (UNIX)
    set(PVR_SDK_DIRECTORY $ENV{HOME}/Native_SDK)
    set(PVR_SDK_INC "${PVR_SDK_DIRECTORY}/framework"
                    "${PVR_SDK_DIRECTORY}/include"
                    )
    set(PVR_SDK_LIB "${PVR_SDK_DIRECTORY}/build/framework/PVRShell/libPVRShell.a"
                    "${PVR_SDK_DIRECTORY}/build/framework/PVRAssets/libPVRAssets.a"
                    "${PVR_SDK_DIRECTORY}/build/framework/PVRUtils/OpenGLES/libPVRUtilsGles.a"
                    "${PVR_SDK_DIRECTORY}/build/framework/PVRCore/libPVRCore.a"
                    X11
                    dl
     )
    add_definitions("-DX11")
ENDIF ()

