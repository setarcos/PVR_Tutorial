cmake_minimum_required (VERSION 3.8)

include (../base.cmake)
project (${TUT_PRO})

add_executable (${TUT_PRO} WIN32 "HelloIBL.cpp" "Helmet.h" "Helmet.cpp" "Skybox.h" "Skybox.cpp")

target_include_directories(${TUT_PRO} PUBLIC ${PVR_SDK_INC})
target_link_libraries(${TUT_PRO} PUBLIC ${PVR_SDK_LIB})

add_custom_command(TARGET ${TUT_PRO}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "${PROJECT_SOURCE_DIR}/*.fsh" $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMAND ${CMAKE_COMMAND} -E copy "${PROJECT_SOURCE_DIR}/*.vsh" $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMAND ${CMAKE_COMMAND} -E copy "${PROJECT_SOURCE_DIR}/*.pvr" $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
