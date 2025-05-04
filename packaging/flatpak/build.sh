#!/bin/sh

set -e
cd "${0%/*}"

if [ -z "$(command -v flatpak)" ] || [ -z "$(command -v flatpak-builder)" ] ; then
    echo "You need to install flatpak and flatpak-builder."
    exit 1
fi

flatpak install -y --or-update org.kde.Sdk//6.9
flatpak-builder --repo=qcma-local --force-clean build-flatpak io.gitlab.robxnano.qcma.json
flatpak remote-add --if-not-exists --no-gpg-verify qcma-local ./qcma-local
flatpak install -y --or-update io.gitlab.robxnano.qcma