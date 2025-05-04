#!/bin/sh

set -e
cd "${0%/*}"

if [ -n "$(command -v podman)" ] ; then
    PODMAN="$(command -v podman)"
elif [ -n "$(command -v docker)" ] ; then
    PODMAN="$(command -v docker)"
else
    echo "You need to install podman or docker."
    exit 1
fi

${PODMAN} build --output . --target appimage .
