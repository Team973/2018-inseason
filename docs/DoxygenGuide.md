# How To Generate Javadocs/Doxygen Docs for Code

## Note: Generating Documentation isn't Always Needed. Read below.

#### Using the GitHub Pages for Documentation

Documentation in the GitHub Pages should be kept up-to-date as much as possible. For this reason, you can view code at [team973.github.io](team973.github.io). To keep this up-to-date, always generate regular documentation in your PR.

#### Offline access

If you are offline, you can open the documentation by running the following command:

    bazel run //tools:open-docs

## Generate Regular Documentation

Regular documentation is the recommended way of generating documentation. It will convert 973 code to HTML as well as all code in the `third_party` subdirectory. To generate regular documentation, use the following command:

    bazel run //tools:generate-docs

## Generate Short Documentation

Short documentation is all of the 973 code converted to HTML. It takes significantly less time to generate than the standard documentation. This is not recommended for beginners because it doesn't include WPILIB. This will cause a loss of complete dependency trees as well. To generate short documentation, use the following command:

    bazel run //tools:generate-short-docs
