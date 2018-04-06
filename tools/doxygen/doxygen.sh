#!/bin/bash

doxygen tools/doxygen/Doxyfile
case "$(uname -s)" in
    Linux*)     xdg-open documentation/html/index.html;;
    Darwin*)    open documentation/html/index.html;;
    *)          exit 1;;
esac
