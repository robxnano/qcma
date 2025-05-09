/* Copyright (C) 2025 Rob Hall
 * SPDX-License-Identifier: GPL-3.0-or-later */
 
#include <version.hpp>

const char* Qcma::Common::version() {
    return QCMA_VER;
}
 
const char* Qcma::Common::buildBranch() {
    return QCMA_BUILD_BRANCH;
}
 
const char* Qcma::Common::buildHash() {
    return QCMA_BUILD_HASH;
}
 