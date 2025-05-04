# Copyright (C) 2025 Rob Hall
# SPDX-License-Identifier: BSD-3-Clause

add_executable(qcma_cli WIN32 MACOSX_BUNDLE
    headlessmanager.cpp headlessmanager.h
    main_cli.cpp
    singlecoreapplication.cpp singlecoreapplication.h
)

target_link_libraries(qcma_cli PRIVATE qcma_common)

install(TARGETS qcma_cli
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(WIN32)
    qt_generate_deploy_app_script(
        TARGET qcma_cli
        OUTPUT_SCRIPT deploy_script
        NO_UNSUPPORTED_PLATFORM_ERROR
    )
    install(SCRIPT ${deploy_script})
elseif(NOT APPLE AND NOT ANDROID)
    install(FILES qcma_cli.1 DESTINATION ${CMAKE_INSTALL_MANDIR}/man1)
endif()
