#!/bin/sh

## This script is managed by puppet.

HDF_SRC=/vagrant/hhvm
HDF_DEST=/etc/hhvm

cp $HDF_SRC/* $HDF_DEST/.
