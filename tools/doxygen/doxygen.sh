#!/bin/bash
set -e

if [[ $1 = 'short' ]]; then
    echo "Creating Doxyfile..."
    cp tools/doxygen/Doxyfile.in tools/doxygen/Doxyfile
    sed 's|$QUIET_OPTION|NO|g' <tools/doxygen/Doxyfile >tools/doxygen/Doxyfile
    sed 's|$WARN_OPTION|YES|g' <tools/doxygen/Doxyfile >tools/doxygen/Doxyfile
    sed 's|$WARN_UNDOC_OPTION|YES|g' <tools/doxygen/Doxyfile >tools/doxygen/Doxyfile
    sed 's|$WARN_DOC_ERROR_OPTION|YES|g' <tools/doxygen/Doxyfile >tools/doxygen/Doxyfile
    sed 's|$INPUT_ITEMS|docs README.md lib src|g' <tools/doxygen/Doxyfile >tools/doxygen/Doxyfile
    echo "Generating short docs..."
    doxygen tools/doxygen/Doxyfile
    rm tools/doxygen/Doxyfile
elif [[ $1 = 'open' ]]; then
    echo
else
    echo "Creating Doxyfile..."
    cp tools/doxygen/Doxyfile.in tools/doxygen/Doxyfile
    sed 's|$QUIET_OPTION|YES|g' <tools/doxygen/Doxyfile >tools/doxygen/Doxyfile
    sed 's|$WARN_OPTION|NO|g' <tools/doxygen/Doxyfile >tools/doxygen/Doxyfile
    sed 's|$WARN_UNDOC_OPTION|NO|g' <tools/doxygen/Doxyfile >tools/doxygen/Doxyfile
    sed 's|$WARN_DOC_ERROR_OPTION|NO|g' <tools/doxygen/Doxyfile >tools/doxygen/Doxyfile
    sed 's|$INPUT_ITEMS|docs README.md lib src third_party|g' <tools/doxygen/Doxyfile >tools/doxygen/Doxyfile
    echo "Generating docs..."
    doxygen tools/doxygen/Doxyfile
    rm tools/doxygen/Doxyfile
fi

echo "Opening..."
case "$(uname -s)" in
    Linux*)     xdg-open docs/doxygen/index.html;;
    Darwin*)    open docs/doxygen/index.html;;
    *)          exit 1;;
esac
