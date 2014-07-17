#!/bin/bash

PROJECT_ROOT=/vagrant
LIB_ROOT=/usr/share/hhvm/hack
LIB_PATH=hhi

HHI_SOURCE=$LIB_ROOT/$LIB_PATH
HHI_DEST=$PROJECT_ROOT/$LIB_PATH

if [ ! -d $HHI_DEST ]; then
  if [ -d $HHI_SOURCE ]; then
    cp -R $HHI_SOURCE $HHI_DEST
  fi
fi
