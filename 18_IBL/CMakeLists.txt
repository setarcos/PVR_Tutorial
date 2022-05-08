cmake_minimum_required (VERSION 3.8)

include (../base.cmake)
project (${TUT_PRO})

add_executable (${TUT_PRO} WIN32 "HelloIBL.cpp" "Helmet.h" "Helmet.cpp" "Skybox.h" "Skybox.cpp")

target_include_directories(${TUT_PRO} PUBLIC ${PVR_SDK_INC})
target_link_libraries(${TUT_PRO} PUBLIC ${PVR_SDK_LIB})

add_custom_command(TARGET ${TUT_PRO}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "${PROJECT_SOURCE_DIR}/FragShader.fsh" $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMAND ${CMAKE_COMMAND} -E copy "${PROJECT_SOURCE_DIR}/VertShader.vsh" $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMAND ${CMAKE_COMMAND} -E copy "${PROJECT_SOURCE_DIR}/SkyFragShader.fsh" $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMAND ${CMAKE_COMMAND} -E copy "${PROJECT_SOURCE_DIR}/SkyVertShader.vsh" $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMAND ${CMAKE_COMMAND} -E copy "${PROJECT_SOURCE_DIR}/brdfLUT.pvr" $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMAND ${CMAKE_COMMAND} -E copy "${PROJECT_SOURCE_DIR}/Default_normal.pvr" $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMAND ${CMAKE_COMMAND} -E copy "${PROJECT_SOURCE_DIR}/Default_albedo.pvr" $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMAND ${CMAKE_COMMAND} -E copy "${PROJECT_SOURCE_DIR}/Default_emissive.pvr" $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMAND ${CMAKE_COMMAND} -E copy "${PROJECT_SOURCE_DIR}/Default_occlusionRoughnessMetallic.pvr" $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMAND ${CMAKE_COMMAND} -E copy "${PROJECT_SOURCE_DIR}/irradiance.pvr" $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMAND ${CMAKE_COMMAND} -E copy "${PROJECT_SOURCE_DIR}/prefiltered.pvr" $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMAND ${CMAKE_COMMAND} -E copy "${PROJECT_SOURCE_DIR}/Skybox.pvr" $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMAND ${CMAKE_COMMAND} -E copy "${PROJECT_SOURCE_DIR}/damagedHelmet.bin" $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMAND ${CMAKE_COMMAND} -E copy "${PROJECT_SOURCE_DIR}/damagedHelmet.gltf" $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
