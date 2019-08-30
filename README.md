# BLERocket



## Setup

- https://docs.platformio.org/en/latest/installation.html#python-package-manager
- https://www.sfml-dev.org/tutorials/2.5/start-linux.php
- https://capnproto.org/install.html (or maybe https://github.com/google/flatbuffers/releases ?)

## Links

- https://docs.platformio.org/en/latest/boards/espressif32/lolin_d32_pro.html


## Errata

`/home/semartin/.platformio/packages/framework-arduinoespressif32/cores/esp32/Arduino.h:172:39: error: ISO C++ forbids declaration of 'makeWord' with no type [-fpermissive]`

Comment out Arduino #define for word()


```
/usr/local/include/capnp/common.h:325:90: error: 'int capnp::word::makeWord()' cannot be defaulted
 class word { uint64_t content KJ_UNUSED_MEMBER; KJ_DISALLOW_COPY(word); public: word() = default; };
 ```

 Rm the `= default` from /usr/local/include/capnp/common.h

Photos: https://photos.app.goo.gl/SCY7WTNyaFZkhxnp9
