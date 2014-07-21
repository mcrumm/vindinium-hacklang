#!/bin/bash

export DEBIAN_FRONTEND=noninteractive

VAGRANT_CORE_FOLDER=$(cat '/.puppet-stuff/vagrant-core-folder.txt')

EXEC_ONCE_DIR="$1"
EXEC_ALWAYS_DIR="$2"

shopt -s nullglob
files=("${VAGRANT_CORE_FOLDER}"/files/"${EXEC_ONCE_DIR}"/*)

if [[ (${#files[@]} -gt 0) ]]; then
    echo "Running files in files/${EXEC_ONCE_DIR}"

    if [ ! -d "/.puppet-stuff/${EXEC_ONCE_DIR}-ran" ]; then
       mkdir "/.puppet-stuff/${EXEC_ONCE_DIR}-ran"
       echo "Created directory /.puppet-stuff/${EXEC_ONCE_DIR}-ran"
    fi

    find "${VAGRANT_CORE_FOLDER}/files/${EXEC_ONCE_DIR}" -maxdepth 1 -not -path '*/\.*' -type f \( ! -iname "empty" \) -exec cp -n '{}' "/.puppet-stuff/${EXEC_ONCE_DIR}-ran" \;
    find "/.puppet-stuff/${EXEC_ONCE_DIR}-ran" -maxdepth 1 -type f -exec chmod +x '{}' \; -exec {} \; -exec sh -c '>{}' \;
    echo "Finished running files in files/${EXEC_ONCE_DIR}"
    echo "To run again, delete file(s) you want rerun in /.puppet-stuff/${EXEC_ONCE_DIR}-ran or the whole folder to rerun all"
fi

echo "Running files in files/${EXEC_ALWAYS_DIR}"
find "${VAGRANT_CORE_FOLDER}/files/${EXEC_ALWAYS_DIR}" -maxdepth 1 -not -path '*/\.*' -type f \( ! -iname "empty" \) -exec chmod +x '{}' \; -exec {} \;
echo "Finished running files in files/${EXEC_ALWAYS_DIR}"
