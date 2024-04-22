set(APP_NAME ${PROJECT_NAME})
qt_add_executable(${APP_NAME} main.cpp UiApplication.cpp ChatManager.cpp ../common/Protocol.cpp)

qt_add_qml_module(${APP_NAME}
    URI ${APP_NAME}
    QML_FILES main.qml
)

target_compile_definitions(${APP_NAME} PRIVATE ${GLOBAL_COMPILE_DEFINITIONS})
target_link_libraries(${APP_NAME} PRIVATE Qt6::Quick)

set_target_properties(${APP_NAME} PROPERTIES WIN32_EXECUTABLE ON)
