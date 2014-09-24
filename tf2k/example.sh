#!/bin/bash
../build/tf2k/tf2k -e "%artist%/\$if(%album%,%album%/,)%title%" -f test.flac
