#!/bin/bash

COMPOSER_INSTALL_URL="https://getcomposer.org/composer.phar"
COMPOSER_GLOBAL_BIN="/usr/local/bin/composer"
COMPOSER_BASH_URL="https://raw.githubusercontent.com/iArren/composer-bash-completion/master/composer"
COMPOSER_BASH_PATH="/etc/bash_completion.d/composer"

if [ -f $COMPOSER_GLOBAL_BIN ]; then
  $COMPOSER_GLOBAL_BIN self-update
else
  wget -O $COMPOSER_GLOBAL_BIN $COMPOSER_INSTALL_URL
  chmod +x $COMPOSER_GLOBAL_BIN
fi

if [ ! -f $COMPOSER_BASH_PATH ]; then
    wget -O $COMPOSER_BASH_PATH $COMPOSER_BASH_URL
fi
