#!/bin/bash
wget -P /tmp https://github.com/Ahmedsaed/alx-low_level_programming/raw/main/0x18-dynamic_libraries/libwin.so
export LD_PRELOAD=/tmp/libwin.so
