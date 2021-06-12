cmake_minimum_required(VERSION 3.12)
project(QuickVSG VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_VS_INCLUDE_INSTALL_TO_DEFAULT_BUILD ON)
set(CMAKE_DEBUG_POSTFIX "d" CACHE STRING "add a postfix, usually d on windows")
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE PATH "" FORCE)

find_package(Qt6 COMPONENTS Core REQUIRED CONFIG)
find_package(Qt6 COMPONENTS Gui REQUIRED CONFIG)
find_package(Qt6 COMPONENTS Qml REQUIRED CONFIG)
find_package(Qt6 COMPONENTS Quick REQUIRED CONFIG)

get_target_property(_qmake_executable Qt::qmake IMPORTED_LOCATION)
get_filename_component(_qt_bin_dir "${_qmake_executable}" DIRECTORY)

find_package(Vulkan REQUIRED)
find_package(vsg_glslang REQUIRED)
find_package(vsg REQUIRED)

add_subdirectory(src)
add_subdirectory(demo)
