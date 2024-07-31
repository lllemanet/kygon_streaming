set(APP_NAME ${PROJECT_NAME})
qt_add_executable(${APP_NAME}
    main.cpp
    UiApplication.cpp
    ChatManager.cpp
    ../common/Protocol.cpp
    ../common/UserDto.cpp
)

qt_add_qml_module(${APP_NAME}
    URI ${APP_NAME}
    QML_FILES
        qml/main.qml
        qml/Authentication.qml
        qml/ActiveUsers.qml
        qml/Chat.qml
        qml/MessageInput.qml
        qml/UserMessages.qml
        qml/LeftPanel.qml
)

target_compile_definitions(${APP_NAME} PRIVATE ${GLOBAL_COMPILE_DEFINITIONS})
target_link_libraries(${APP_NAME} PRIVATE Qt6::Quick)

set_target_properties(${APP_NAME} PROPERTIES WIN32_EXECUTABLE ON)

# For Qt Creator IntelliSense
set(QML_IMPORT_PATH
    ${CMAKE_CURRENT_BINARY_DIR}
    CACHE STRING ""
    FORCE
)
