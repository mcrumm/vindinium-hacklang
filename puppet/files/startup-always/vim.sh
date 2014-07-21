#!/bin/bash

USER="vagrant"
GROUP="vagrant"
VIMDIR="/home/vagrant/.vim"
PATHOGEN_URL="https://tpo.pe/pathogen.vim"
PATHOGEN_AUTOLOAD_DIR="$VIMDIR/autoload"
PATHOGEN_BUNDLE_DIR="$VIMDIR/bundle"
PATHOGEN_PATH="$PATHOGEN_AUTOLOAD_DIR/pathogen.vim"

# ensure user .vim directory exists
if [ ! -d $VIMDIR ]; then
  mkdir $VIMDIR
fi

# ensure pathogen is installed
if [ ! -d $PATHOGEN_AUTOLOAD_DIR ]; then
  mkdir -p $PATHOGEN_AUTOLOAD_DIR $PATHOGEN_BUNDLE_DIR && \
  curl -LSso $PATHOGEN_PATH $PATHOGEN_URL
  chown -R $USER:$GROUP $PATHOGEN_AUTOLOAD_DIR $PATHOGEN_BUNDLE_DIR
fi

# ensure vim-hack is installed
if [ ! -d $PATHOGEN_BUNDLE_DIR/vim-hack ]; then
  git clone git://github.com/hhvm/vim-hack.git $PATHOGEN_BUNDLE_DIR/vim-hack
  chown -R $USER:$GROUP $PATHOGEN_BUNDLE_DIR/vim-hack
fi
