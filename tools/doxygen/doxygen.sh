#!/bin/bash
set -e

case "$(uname -s)" in
    Linux*)     machine=Linux;;
    Darwin*)    machine=Mac;;
    *)          machine="UNKNOWN"
esac
echo ${machine}

if [[ $1 = 'short' ]]; then
  echo "Creating Doxyfile..."
  cp tools/doxygen/Doxyfile.in tools/doxygen/Doxyfile
  if [ "$(uname)" == "Darwin" ]; then
    sed -i '' 's|$QUIET_OPTION|NO|g' tools/doxygen/Doxyfile
    sed -i '' 's|$WARN_OPTION|YES|g' tools/doxygen/Doxyfile
    sed -i '' 's|$WARN_UNDOC_OPTION|YES|g' tools/doxygen/Doxyfile
    sed -i '' 's|$WARN_DOC_ERROR_OPTION|YES|g' tools/doxygen/Doxyfile
    sed -i '' 's|$INPUT_ITEMS|docs README.md lib src|g' tools/doxygen/Doxyfile
  elif [ "$(expr substr $(uname -s) 1 5)" == "Linux" ]; then
    sed 's|$QUIET_OPTION|NO|g' tools/doxygen/Doxyfile
    sed 's|$WARN_OPTION|YES|g' tools/doxygen/Doxyfile
    sed 's|$WARN_UNDOC_OPTION|YES|g' tools/doxygen/Doxyfile
    sed 's|$WARN_DOC_ERROR_OPTION|YES|g' tools/doxygen/Doxyfile
    sed 's|$INPUT_ITEMS|docs README.md lib src|g' tools/doxygen/Doxyfile
  fi
  echo "Generating short docs..."
  doxygen tools/doxygen/Doxyfile
  rm tools/doxygen/Doxyfile
  zip -r $2 tools/doxygen/docs/doxygen
  rm -r tools/doxygen/docs
  echo "Done generating. Extract the zip file in bazel-out for the generated files."
else
  echo "Creating Doxyfile..."
  cp tools/doxygen/Doxyfile.in tools/doxygen/Doxyfile
  if [ "$(uname)" == "Darwin" ]; then
    sed -i '' 's|$QUIET_OPTION|NO|g' tools/doxygen/Doxyfile
    sed -i '' 's|$WARN_OPTION|YES|g' tools/doxygen/Doxyfile
    sed -i '' 's|$WARN_UNDOC_OPTION|YES|g' tools/doxygen/Doxyfile
    sed -i '' 's|$WARN_DOC_ERROR_OPTION|YES|g' tools/doxygen/Doxyfile
    sed -i '' 's|$INPUT_ITEMS|docs README.md lib third_party|g' tools/doxygen/Doxyfile
  elif [ "$(expr substr $(uname -s) 1 5)" == "Linux" ]; then
    sed 's|$QUIET_OPTION|NO|g' tools/doxygen/Doxyfile
    sed 's|$WARN_OPTION|YES|g' tools/doxygen/Doxyfile
    sed 's|$WARN_UNDOC_OPTION|YES|g' tools/doxygen/Doxyfile
    sed 's|$WARN_DOC_ERROR_OPTION|YES|g' tools/doxygen/Doxyfile
    sed 's|$INPUT_ITEMS|docs README.md lib src third_party|g' tools/doxygen/Doxyfile
  fi
  echo "Generating short docs..."
  doxygen tools/doxygen/Doxyfile
  rm tools/doxygen/Doxyfile
  zip -r $1 tools/doxygen/docs/doxygen
  rm -r tools/doxygen/docs
  echo "Done generating. Extract the zip file in bazel-out for the generated files."
fi
