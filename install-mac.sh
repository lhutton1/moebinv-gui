#!/usr/bin/env bash

# build moebinv-gui
mkdir moebinv-gui-build
cd moebinv-gui-build
qmake -makefile ../moebinv-gui.pro
make
make install
