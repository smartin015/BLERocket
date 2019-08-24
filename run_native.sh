#!/bin/bash
#!/bin/bash

rm lib/proto/*.capnp.cpp
rm lib/proto/*.capnp.h
capnp compile -oc++ ./lib/proto/*
mv lib/proto/game_objects.capnp.c++ lib/proto/game_objects.capnp.cpp
mv lib/proto/nav.capnp.c++ lib/proto/nav.capnp.cpp
mv lib/proto/status.capnp.c++ lib/proto/status.capnp.cpp
pio run -e native
.pio/build/native/program
