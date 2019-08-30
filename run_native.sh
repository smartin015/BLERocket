#!/bin/bash
#!/bin/bash
flatc --cpp --gen-object-api -o ./lib/proto ./lib/proto/*.fbs
pio run -e native
.pio/build/native/program
