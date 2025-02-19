#!/bin/sh
find ./tests -regex '.*\.\(cpp\|hpp\|c\|h\)' -exec clang-format -style=file -i {} \;
find ./hnswlib -regex '.*\.\(cpp\|hpp\|c\|h\)' -exec clang-format -style=file -i {} \;
find ./examples -regex '.*\.\(cpp\|hpp\|c\|h\)' -exec clang-format -style=file -i {} \;