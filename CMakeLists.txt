# Copyright (C) 2025 Rob Hall
# SPDX-License-Identifier: BSD-3-Clause

cmake_minimum_required(VERSION 3.16...4.0)
project(Qcma VERSION 0.5.1 LANGUAGES C CXX)

include(FetchContent)
include(FindPkgConfig)
include(GNUInstallDirs)
if(WIN32)
    set(CMAKE_INSTALL_BINDIR .)
    include(CPack)
endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_COLOR_DIAGNOSTICS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# disabled for now as recent FFmpeg versions don't work
option(ENABLE_FFMPEG "Enable FFmpeg" OFF)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(USE_QT6 "Build with Qt 6" ON)
if(LINUX AND NOT ANDROID)
    option(INSTALL_SERVICE "Install systemd service files" OFF)
    set(SYSTEMD_UNIT_DIR "lib/systemd" CACHE PATH "systemd unit files directory root (lib/systemd)")
endif()

execute_process(COMMAND git describe --tags
                OUTPUT_VARIABLE QCMA_VER
                ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND git rev-parse --abbrev-ref HEAD
                OUTPUT_VARIABLE QCMA_BUILD_BRANCH
                ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND git rev-parse --short HEAD
                OUTPUT_VARIABLE QCMA_BUILD_HASH
                ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)

if(NOT QCMA_VER)
    set(QCMA_VER "v${PROJECT_VERSION}")
endif()

if(USE_QT6)
    set(QT_VERSION_MAJOR 6)
    set(QT_VERSION_MINIMUM 6.3.0)
else()
    set(QT_VERSION_MAJOR 5)
    set(QT_VERSION_MINIMUM 5.15.0)
endif()

find_package(Qt${QT_VERSION_MAJOR} ${QT_VERSION_MINIMUM} REQUIRED
             COMPONENTS Core Gui Network Sql Widgets LinguistTools)

find_package(Iconv REQUIRED)

FetchContent_Declare(VitaMTP
    GIT_REPOSITORY https://github.com/robxnano/vitamtp.git
    GIT_TAG        66555f2c1a06b524dd830f63e90867354e099978
)

add_subdirectory(common)
if(ANDROID)
    add_subdirectory(android)
else()
    add_subdirectory(gui)
    if(UNIX AND NOT MACOS)
        add_subdirectory(cli)
    endif()
endif()

configure_file(packaging/systemd/user/qcma.service.in user/qcma.service @ONLY)
configure_file(packaging/systemd/system/qcma.service.in system/qcma.service @ONLY)

if(INSTALL_SERVICE)
    # Unit files are always installed in lib/systemd/{user,system}
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/user/qcma.service
            DESTINATION ${SYSTEMD_UNIT_DIR}/user)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/systemd/qcma.service
            DESTINATION ${SYSTEMD_UNIT_DIR}/system)
endif()
