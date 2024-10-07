# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

project(WaifuGalEngine LANGUAGES CXX)

qt_standard_project_setup()

include_directories(.)
qt_add_resources(TestImage ../testres/image.qrc)

qt_add_executable(WaifuGalEngine WIN32 MACOSX_BUNDLE
    main.cpp
    textbar.h
    textbar.cpp
    choiceview.h
    choiceview.cpp
    stage.h
    stage.cpp
    game.h
    game.cpp
    gameitem.h
    gameitem.cpp
    imageprovider.h
    imageprovider.cpp
    galaction.h

    presets/basicaction.h
    presets/basicaction.cpp
    presets/basicmotion.h
    presets/basicmotion.cpp

    ${TestImage}
)

target_link_libraries(WaifuGalEngine PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
)

qt_add_qml_module(WaifuGalEngine
    URI OpenGLUnderQML
    QML_FILES qml/main.qml
    RESOURCE_PREFIX /
    NO_RESOURCE_TARGET_PATH
)

install(TARGETS WaifuGalEngine
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_qml_app_script(
    TARGET WaifuGalEngine
    OUTPUT_SCRIPT deploy_script
    MACOS_BUNDLE_POST_BUILD
    NO_UNSUPPORTED_PLATFORM_ERROR
    DEPLOY_USER_QML_MODULES_ON_UNSUPPORTED_PLATFORM
)
install(SCRIPT ${deploy_script})
