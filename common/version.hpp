/* Copyright (C) 2025 Rob Hall
 * SPDX-License-Identifier: GPL-3.0-or-later */

#ifndef QCMA_VERSION_H
#define QCMA_VERSION_H

namespace Qcma::Common {
    const char* version();
    const char* buildBranch();
    const char* buildHash();
}

#endif // QCMA_VERSION_H
