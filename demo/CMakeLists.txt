set(TARGET_NAME demo)

qt_add_executable(${TARGET_NAME}
    main.cpp
    main.qml
    qml.qrc
)

target_link_libraries(${TARGET_NAME} PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Qml
    Qt::Quick
    libquickvsg
)

install(TARGETS ${TARGET_NAME} RUNTIME DESTINATION demo)

set_target_properties(${TARGET_NAME} PROPERTIES 
    COMPILE_FLAGS "/MP"
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_INSTALL_PREFIX}/bin"
    VS_DEBUGGER_COMMAND "${CMAKE_INSTALL_PREFIX}/demo/$<TARGET_FILE_NAME:${TARGET_NAME}>"
    VS_DEBUGGER_ENVIRONMENT "PATH=${_qt_bin_dir};${CMAKE_INSTALL_PREFIX};\nQML2_IMPORT_PATH=${CMAKE_INSTALL_PREFIX}\nQT_QPA_PLATFORM_PLUGIN_PATH=${_qt_bin_dir}/../plugins/platforms"
)