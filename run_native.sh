#!/bin/bash
#!/bin/bash

rm lib/proto/*.capnp.cpp
rm lib/proto/*.capnp.h
capnp compile -oc++ ./lib/proto/*
mv lib/proto/game.capnp.c++ lib/proto/game.capnp.cpp
mv lib/proto/nav.capnp.c++ lib/proto/nav.capnp.cpp
mv lib/proto/message.capnp.c++ lib/proto/message.capnp.cpp
pio run -e native
.pio/build/native/program
