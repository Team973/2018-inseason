#!/bin/bash
set -e

if [[ $1 = 'short' ]]; then
  echo "Creating Doxyfile..."
  cp tools/doxygen/Doxyfile.in tools/doxygen/Doxyfile
  sed -i '' 's|$QUIET_OPTION|NO|g' tools/doxygen/Doxyfile
  sed -i '' 's|$WARN_OPTION|YES|g' tools/doxygen/Doxyfile
  sed -i '' 's|$WARN_UNDOC_OPTION|YES|g' tools/doxygen/Doxyfile
  sed -i '' 's|$WARN_DOC_ERROR_OPTION|YES|g' tools/doxygen/Doxyfile
  sed -i '' 's|$INPUT_ITEMS|docs README.md lib src|g' tools/doxygen/Doxyfile
  echo "Generating short docs..."
  doxygen tools/doxygen/Doxyfile
  rm tools/doxygen/Doxyfile
  zip -r $2 tools/doxygen/docs/doxygen
  rm -r tools/doxygen/docs
  echo "Done generating. Run open-docs to open the generated files."
else
  echo "Creating Doxyfile..."
  cp tools/doxygen/Doxyfile.in tools/doxygen/Doxyfile
  sed -i '' 's|$QUIET_OPTION|NO|g' tools/doxygen/Doxyfile
  sed -i '' 's|$WARN_OPTION|YES|g' tools/doxygen/Doxyfile
  sed -i '' 's|$WARN_UNDOC_OPTION|YES|g' tools/doxygen/Doxyfile
  sed -i '' 's|$WARN_DOC_ERROR_OPTION|YES|g' tools/doxygen/Doxyfile
  sed -i '' 's|$INPUT_ITEMS|docs README.md lib src third_party|g' tools/doxygen/Doxyfile
  echo "Generating short docs..."
  doxygen tools/doxygen/Doxyfile
  rm tools/doxygen/Doxyfile
  zip -r $1 tools/doxygen/docs/doxygen
  rm -r tools/doxygen/docs
  echo "Done generating. Run open-docs to open the generated files."
fi
