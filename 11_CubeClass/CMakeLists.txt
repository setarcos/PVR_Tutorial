cmake_minimum_required (VERSION 3.8)

include (../base.cmake)
project (${TUT_PRO})

add_executable (${TUT_PRO} WIN32 "HelloPVR.cpp" "Triangle.h" "Triangle.cpp")

target_include_directories(${TUT_PRO} PUBLIC ${PVR_SDK_INC})
target_link_libraries(${TUT_PRO} PUBLIC ${PVR_SDK_LIB})

add_custom_command(TARGET ${TUT_PRO}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "${PROJECT_SOURCE_DIR}/FragShader.fsh" $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMAND ${CMAKE_COMMAND} -E copy "${PROJECT_SOURCE_DIR}/VertShader.vsh" $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMAND ${CMAKE_COMMAND} -E copy "${PROJECT_SOURCE_DIR}/Image.pvr" $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
