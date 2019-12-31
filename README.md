# moebinv-gui

This QT application provides a GUI for the moebinv package.

__Note:__ Further development has made on this project. For the most recent up-to-date application, along with moebinv itself: http://moebinv.sourceforge.net/

## Introduction

The moebinv library allows for manipulations in non euclidean geometry. This application is a gui for use with the moebinv library.

## Installation

Prerequisites:
- CLN
- GiNaC
- moebinv

Installation on Mac:

__1. Install Homebrew.__

  Paste this into a terminal:
  `/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"`

  You may need to agree to the installation of Xcode.

__2. Make sure that your mac has a GCC version greater than 4.4.__

  You can do this by typing `gcc --version`

  If not excecute:
  `brew install https://raw.github.com/Homebrew/homebrew-dupes/master/gcc.rb
  rm -v /usr/bin/{cc,gcc,c++,g++}
  ln -sv /usr/local/bin/gcc-4.x /usr/bin/cc
  ln -sv /usr/local/bin/gcc-4.x /usr/bin/gcc
  ln -sv /usr/local/bin/c++-4.x /usr/bin/c++
  ln -sv /usr/local/bin/g++-4.x /usr/bin/g++`

__3. Install GiNaC and Cmake using homebrew:__
  `brew install ginac
  brew install cmake`

__4. Install MoebInv__

  - Download the latest version of MoebInv here: https://sourceforge.net/p/moebinv/
  - Navigate to the src file in a terminal
  - Type `make`

  - Make sure MoebInv-gui can find the library files by either:
    - Placing `figure.h` and `cycle.h` in `/usr/local/include` and placing `libfigure.so` and `libcycle.so` in `/usr/local/lib`
    - Or by placing the files in the lib folder in the downloaded moebinv-gui.

__5. Install Qt using home brew:__
  `brew install qt`

__6. Install MoebInv-gui__
  - clone the moebInv-gui repository from: https://github.com/lhutton1/moebinv-gui by executing:
    `git clone https://github.com/lhutton1/moebinv-gui`
  - open a terminal in this directory or directly after executing the clone command execute `cd moebinv-gui`
  - build the make file by executing `qmake`
  - compile the application by executing `make`
  - install the documentation by running `make install`
  - run the application by execting `./moebinv-gui`

  or

  - run the .sh script `mac-install.sh`
