#!/bin/bash

# Authorize use of X display
XAUTH=/tmp/.docker.xauth
if [ ! -f $XAUTH ]
then
    xauth_list=$(xauth nlist :0 | sed -e 's/^..../ffff/')
    if [ ! -z "$xauth_list" ]
    then
        echo $xauth_list | xauth -f $XAUTH nmerge -
    else
        touch $XAUTH
    fi
    chmod a+r $XAUTH
fi

# Optional device path as first argument, to allow for flashing to device from container.
[[ $1 ]] && DEVMAPFLAG="--device=$1:/dev/ttyUSB0" || DEVMAPFLAG=""

# Include display/NVIDIA environment vars and use
# nvidia runtime to allow for GLX display from inside container
RESOLVE_PATH=$(pwd)
docker run -v $RESOLVE_PATH:/volume \
  --runtime=nvidia \
  --env="NVIDIA_VISIBLE_DEVICES=all" \
  --env="NVIDIA_DRIVER_CAPABILITIES=${NVIDIA_DRIVER_CAPABILITIES}graphics" \
  --env="QT_X11_NO_MITSHM=1" \
  --env="DISPLAY=${DISPLAY}" \
  --env="XAUTHORITY=${XAUTH}" \
  -v /tmp/.X11-unix:/tmp/.X11-unix:rw \
  -v /tmp/.docker.xauth:/tmp/.docker.xauth \
  ${DEVMAPFLAG} \
  -it blerocket:latest
