#!/bin/bash

if [[ $1 != 'short' ]]; then
  sed 's/CHANGE_ME/YES/g' tools/doxygen/Doxyfile.in > tools/doxygen/Doxyfile.long
  sed 's/lib src/lib src third_party/g' tools/doxygen/Doxyfile.long > tools/doxygen/Doxyfile
else
  sed 's/CHANGE_ME/NO/g' tools/doxygen/Doxyfile.in > tools/doxygen/Doxyfile
fi

doxygen tools/doxygen/Doxyfile

case "$(uname -s)" in
    Linux*)     xdg-open docs/doxygen/index.html;;
    Darwin*)    open docs/doxygen/index.html;;
    *)          exit 1;;
esac
