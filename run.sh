#!/usr/bin/env bash
# Run C0 programs inside the Docker container

docker run --rm \
    -v "$PWD":/work \
    -w /work \
    cmu \
    cc0 "$@"

