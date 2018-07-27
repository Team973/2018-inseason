# How To Generate Javadocs/Doxygen Docs for Code

## Generate Regular Documentation

Regular documentation is the recommended way of generating documentation. It will document 973 code and `third_party` code as HTML. A zip file containing the docs will be generated in `bazel-out`. To generate regular documentation, use the following command:

    bazel run //tools/doxygen:generate-docs

## Generate Short Documentation

Short documentation documents only 973 code. It takes significantly less time to generate than the standard documentation. This is not recommended for beginners because it doesn't include `third_party`. This will cause a loss of complete dependency trees as well. A zip file containing the docs will be generated in `bazel-out`. To generate short documentation, use the following command:

    bazel run //tools/doxygen:generate-short-docs
