set(TARGET_NAME MercuryRuntime)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---- 添加源文件 ----
# 递归添加源文件
file(GLOB_RECURSE HEADER_FILES CONFIGURE_DEPENDS "*.h")
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "*.cpp")

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${HEADER_FILES} ${SOURCE_FILES})

# ---- 创建库 ----
# 作为库被构建
add_library(${TARGET_NAME} ${HEADER_FILES} ${SOURCE_FILES})

# 链接依赖库
target_link_libraries(${TARGET_NAME} PUBLIC glfw)
target_link_libraries(${TARGET_NAME} PUBLIC ${vulkan_lib})

# begin Vulkan
target_include_directories(
    ${TARGET_NAME}
    PUBLIC $<BUILD_INTERFACE:${vulkan_include}>)

target_include_directories(
    ${TARGET_NAME}
    PUBLIC $<BUILD_INTERFACE:${LIBRARY_DIR}/VulkanSDK/include/vma>
)

# end Vulkan

# 将目录包含到对应目标里，不写这句话可就找不到.h文件了
target_include_directories(
    ${TARGET_NAME}
    PUBLIC $<BUILD_INTERFACE:${ENGINE_ROOT_DIR}/source>
    $<INSTALL_INTERFACE:include/${TARGET_NAME}-${PROJECT_VERSION}>
)

target_include_directories(
    ${TARGET_NAME}
    PUBLIC $<BUILD_INTERFACE:${ENGINE_ROOT_DIR}/source/runtime>
    $<INSTALL_INTERFACE:include/${TARGET_NAME}-${PROJECT_VERSION}>
)

# shader 显式要求cmake先编译${SHADER_COMPILE_TARGET}
add_dependencies(${TARGET_NAME} ${SHADER_COMPILE_TARGET}) 
target_include_directories(
    ${TARGET_NAME}
    PUBLIC $<BUILD_INTERFACE:${ENGINE_ROOT_DIR}/shader/generated/cpp>)

# 将该模块保存到Engine目录下
set_target_properties(${TARGET_NAME} PROPERTIES CXX_STANDARD 17)
set_target_properties(${TARGET_NAME} PROPERTIES FOLDER "Engine")