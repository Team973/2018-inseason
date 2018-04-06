#!/bin/bash

sed "s#CHANGE_ME#$1#g" tools/doxygen/Doxyfile.in > tools/doxygen/Doxyfile
doxygen tools/doxygen/Doxyfile
case "$(uname -s)" in
    Linux*)     xdg-open documentation/html/index.html;;
    Darwin*)    open documentation/html/index.html;;
    *)          exit 1;;
esac
