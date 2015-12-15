#!/bin/bash

export CC=${USE_CC:-$CC}

$CC --version

aclocal
autoconf
autoheader
automake --add-missing
./configure && make && make test
