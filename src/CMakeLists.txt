set(TARGET_NAME libquickvsg)

set(PUBLIC_HEADERS
    qv_global.h
    qv_canvas.h
)

set(PRIVATE_HEADERS
    qv_canvas_renderer.h
)

set(SOURCES
    qv_global.cpp
    qv_canvas.cpp
    qv_canvas_renderer.cpp
)

add_library(${TARGET_NAME} SHARED ${PUBLIC_HEADERS} ${PRIVATE_HEADERS}
    ${SOURCES}
)

target_compile_definitions(${TARGET_NAME} 
    PRIVATE QUICKVSG_LIBRARY
    PUBLIC VK_USE_PLATFORM_WIN32_KHR NOMINMAX
)

target_include_directories(${TARGET_NAME} 
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${TARGET_NAME} 
    PUBLIC 
        Qt::Core
        Qt::Gui
        Qt::Qml
        Qt::Quick 
        Vulkan::Vulkan
        vsg::vsg
)

install(TARGETS ${TARGET_NAME}
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)

install(FILES ${PUBLIC_HEADERS}
    DESTINATION include
)

install(FILES $<TARGET_PDB_FILE:${TARGET_NAME}>
    DESTINATION bin
    CONFIGURATIONS Debug
)