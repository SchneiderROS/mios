#!/bin/sh -e

ROOT=$(dirname "$(realpath $0)")/..
cd ${ROOT}

docker build -t mios_mls -f docker/ml_service/Dockerfile .
docker tag mios_mls:latest msrm/mios_mls:release
docker tag mios_mls:latest collective-control-001.local:5000/mios_mls
