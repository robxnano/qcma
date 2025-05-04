# Copyright (C) 2025 Rob Hall
# SPDX-License-Identifier: BSD-3-Clause

set(CMAKE_AUTOUIC ON)

add_library(qcma_gui OBJECT
    clientmanager.cpp clientmanager.h
    filterlineedit.cpp filterlineedit.h
    forms/backupitem.cpp forms/backupitem.h forms/backupitem.ui
    forms/backupmanagerform.cpp forms/backupmanagerform.h forms/backupmanagerform.ui
    forms/configwidget.cpp forms/configwidget.h forms/configwidget.ui
    forms/confirmdialog.cpp forms/confirmdialog.h forms/confirmdialog.ui
    forms/pinform.cpp forms/pinform.h forms/pinform.ui
    forms/progressform.cpp forms/progressform.h forms/progressform.ui
    mainwidget.cpp mainwidget.h
    qtrayicon.cpp qtrayicon.h
    singleapplication.cpp singleapplication.h
    trayindicator.h
    trayindicator_global.h
)

target_link_libraries(qcma_gui PUBLIC
    Qt${QT_VERSION_MAJOR}::Widgets
    qcma_common
)

if(LINUX AND NOT ANDROID)
    pkg_check_modules(libnotify REQUIRED IMPORTED_TARGET libnotify)
    target_link_libraries(qcma_gui PRIVATE PkgConfig::libnotify)
endif()

add_executable(qcma WIN32 MACOSX_BUNDLE main.cpp)
target_link_libraries(qcma PRIVATE qcma_gui)

if(WIN32)
    target_sources(qcma_gui PRIVATE qcma.rc)

    # Build the GUI client as a console application for debug output
    add_executable(qcma_console main.cpp)
    target_link_libraries(qcma_console PRIVATE qcma_gui)
endif()

# Resources
set(gui_resource_files
    "resources/images/edit-clear-locationbar-rtl.png"
    "resources/images/qcma.png"
    "resources/images/qcma_off.png"
    "resources/images/qcma_on.png"
    "resources/images/tray/qcma_off.png"
    "resources/images/tray/qcma_off_16.png"
    "resources/images/tray/qcma_on.png"
    "resources/images/tray/qcma_on_16.png"
)

qt_add_resources(qcma gui PREFIX "/main" FILES ${gui_resource_files})

target_sources(qcma PRIVATE ${qcma_gui})

install(TARGETS qcma
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(WIN32)
    qt_generate_deploy_app_script(
        TARGET qcma
        OUTPUT_SCRIPT deploy_script
        NO_UNSUPPORTED_PLATFORM_ERROR
    )
    install(SCRIPT ${deploy_script})
elseif(NOT APPLE AND NOT ANDROID)
    install(FILES qcma.1
            DESTINATION ${CMAKE_INSTALL_MANDIR}/man1)
    install(FILES resources/io.gitlab.robxnano.qcma.metainfo.xml
            DESTINATION ${CMAKE_INSTALL_DATADIR}/metainfo)
    install(FILES resources/qcma.desktop
            RENAME io.gitlab.robxnano.qcma.desktop
            DESTINATION ${CMAKE_INSTALL_DATADIR}/applications)
    install(FILES resources/images/qcma.png
            RENAME io.gitlab.robxnano.qcma.png
            DESTINATION ${CMAKE_INSTALL_DATADIR}/icons/hicolor/64x64/apps)    
endif()
