FROM ubuntu:19.04
MAINTAINER Scott Martin <smartin015@gmail.com>

RUN apt-get update
RUN apt-get install -y curl git python python-pip bash tmux build-essential cmake libsfml-dev
RUN pip install -U platformio

RUN curl https://codeload.github.com/google/flatbuffers/tar.gz/v1.11.0 -o /tmp/flatbuffers.tar.gz && cd /tmp && tar xvf flatbuffers.tar.gz && mkdir -p /tmp/flatbuffers-1.11.0/build && cd /tmp/flatbuffers-1.11.0/build && cmake .. && make && make install

RUN echo "#!/bin/bash\ncd /volume\ntmux new-session -s dev '/bin/bash'" > /run.sh && chmod a+x /run.sh
ENTRYPOINT /run.sh
