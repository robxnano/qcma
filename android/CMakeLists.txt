# Copyright (C) 2025 Rob Hall
# SPDX-License-Identifier: BSD-3-Clause

find_package(Qt${QT_VERSION_MAJOR} ${QT_VERSION_MINIMUM} REQUIRED COMPONENTS Qml Quick)

add_executable(qcma_android WIN32 MACOSX_BUNDLE
    main_android.cpp
    servicemanager.h
    sevicemanager.cpp
)
qt_add_qml_module(qcma_android
    URI qcma_android
    VERSION ${PROJECT_VERSION}
)

# Avoid collision between executable name and QML module directory (QTBUG-98568).
if(NOT WIN32 AND NOT APPLE)
    set_property(TARGET qcma_android PROPERTY OUTPUT_NAME qcma_android_app)
endif()

target_link_libraries(qcma_android PRIVATE
    Qt${QT_VERSION_MAJOR}::Qml
    Qt${QT_VERSION_MAJOR}::Quick
    qcma_common
)

install(TARGETS qcma_android
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_generate_deploy_qml_app_script(
    TARGET qcma_android
    FILENAME_VARIABLE deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
    DEPLOY_USER_QML_MODULES_ON_UNSUPPORTED_PLATFORM
    MACOS_BUNDLE_POST_BUILD
)
install(SCRIPT ${deploy_script})
