#!/bin/bash

set -euo pipefail #-e fails at the first error, -u treats undeclared variables as errors and -o pipeline fails if any command in the chain fails

FILES="$@"
CC="gcc"
OUTPUT="meow"

# -Werror -Wshadow
CFLAGS="-Wall -Wextra -Wpedantic \
-Wformat=2 -g3 -Og -fstack-protector-strong  -std=c11           \
-D_FORTIFY_SOURCE=2 -Wstrict-overflow=5 -Warray-bounds=2     \
-Wnull-dereference -fsanitize=address,undefined -pedantic-errors"

LDFLAGS=""
LIBS="-lm"

$CC $FILES $CFLAGS $LDFLAGS $LIBS -o "$OUTPUT"