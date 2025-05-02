# Copyright (C) 2025 Rob Hall
# SPDX-License-Identifier: BSD-3-Clause

add_library(qcma_common
    avdecoder.h
    capability.cpp capability.h
    cmabroadcast.cpp cmabroadcast.h
    cmaclient.cpp cmaclient.h
    cmaevent.cpp cmaevent.h
    cmaobject.cpp cmaobject.h
    cmarootobject.cpp cmarootobject.h
    cmautils.cpp cmautils.h
    database.cpp database.h
    dds.cpp dds.h
    httpdownloader.cpp httpdownloader.h
    qlistdb.cpp qlistdb.h
    sforeader.cpp sforeader.h
    sqlitedb.cpp sqlitedb.h
)

target_include_directories(qcma_common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_definitions(qcma_common PUBLIC
    __STDC_CONSTANT_MACROS
    __STDC_FORMAT_MACROS
)

target_link_libraries(qcma_common PUBLIC
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Network
    Qt${QT_VERSION_MAJOR}::Sql
)

pkg_check_modules(libvitamtp IMPORTED_TARGET "libvitamtp >= 2.6.0" QUIET)
if(libvitamtp_FOUND)
    target_link_libraries(qcma_common PUBLIC PkgConfig::libvitamtp)
else()
    FetchContent_MakeAvailable(VitaMTP)
    target_link_libraries(qcma_common PUBLIC VitaMTP::VitaMTP)
endif()

if(MSVC)
    target_compile_definitions(qcma_common PUBLIC
        _CRT_SECURE_NO_WARNINGS
        _CRT_NONSTDC_NO_WARNINGS
    )
    set_source_files_properties(capability.cpp PROPERTIES COMPILE_OPTIONS -Zc:strictStrings-)
else()
    target_compile_options(qcma_common PUBLIC
        -Wall
        -Wdisabled-optimization
        -Wextra
        -Wformat=2
        -Winit-self
        -Wno-format-nonliteral
        -Wno-missing-field-initializers
        -Wno-unused
        -Wno-write-strings
        -Woverloaded-virtual
        -Wundef
    )
endif()

# Resources
set(commonrc_resource_files
    "resources/xml/psp2-updatelist.xml"
)

qt_add_resources(qcma_common commonrc PREFIX "/main" FILES ${commonrc_resource_files})

set(translations_resource_files
    "resources/translations/qcma_cn.ts"
    "resources/translations/qcma_es.ts"
    "resources/translations/qcma_fr.ts"
    "resources/translations/qcma_ja.ts"
)

qt_add_translations(qcma_common TS_FILES ${translations_resource_files})

target_sources(qcma_common PRIVATE ${qcma_commonrc} ${qcma_translations})

if(ENABLE_FFMPEG)
    target_sources(qcma_common PRIVATE avdecoder.cpp)
    target_compile_definitions(qcma_common PUBLIC FFMPEG_ENABLED)

    pkg_check_modules(ffmpeg REQUIRED IMPORTED_TARGET libavcodec libavformat libavutil libswscale)
    target_link_libraries(qcma_common PRIVATE PkgConfig::ffmpeg)
endif()

if(UNIX AND NOT MACOS)
    target_compile_definitions(qcma_common PUBLIC
        _FILE_OFFSET_BITS=64
        _LARGEFILE_SOURCE
    )
endif()

if(WIN32 AND NOT MSVC)
    target_compile_options(qcma_common PUBLIC -mno-ms-bitfields)
endif()

target_compile_definitions(qcma_common PUBLIC "QCMA_VER=\"${QCMA_VER}\"")

if(QCMA_BUILD_BRANCH AND QCMA_BUILD_HASH)
    target_compile_definitions(qcma_common PUBLIC
        "QCMA_BUILD_BRANCH=\"${QCMA_BUILD_BRANCH}\""
        "QCMA_BUILD_HASH=\"${QCMA_BUILD_HASH}\""
    )
endif()

if(BUILD_SHARED_LIBS)
    install(TARGETS qcma_common
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
endif()
