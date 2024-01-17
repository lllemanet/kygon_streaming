qt_add_executable(${PROJECT_NAME} main.cpp)

qt_add_qml_module(${PROJECT_NAME}
    URI ${PROJECT_NAME}
    QML_FILES Main.qml
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Quick)

set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE ON)
