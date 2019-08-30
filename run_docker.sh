#!/bin/bash
RESOLVE_PATH=$(pwd)
docker run -v $RESOLVE_PATH:/volume -it blerocket:latest
