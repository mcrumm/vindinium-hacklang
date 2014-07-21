#!/bin/bash

export DEBIAN_FRONTEND=noninteractive

VAGRANT_CORE_FOLDER=$(echo "$1")

if [[ ! -d '/.puppet-stuff' ]]; then
    mkdir '/.puppet-stuff'
    echo 'Created directory /.puppet-stuff'
fi

touch '/.puppet-stuff/vagrant-core-folder.txt'
echo "${VAGRANT_CORE_FOLDER}" > '/.puppet-stuff/vagrant-core-folder.txt'

