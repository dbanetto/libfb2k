#!/bin/bash
LD_LIBRARY_PATH=./Debug/

./Debug/tf2k -e "%artist%/\$if(%album%,%album%/,)%title%" -f test.flac
