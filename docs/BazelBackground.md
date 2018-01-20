# Bazel Overview
[Bazel](https://bazel.build/) is the internal build tool developed by Google and now open sourced.
## Terminology
All projects must have a `WORKSPACE` file in their top level directory. Only one `WORKSPACE` file is necessary per project.

Projects are made up of packages. A package is a directory containing a `BUILD` file. The `BUILD` file defines rules for building the package.

A rule describes how to build the different parts of a package and where they can be used outside of the package.

To build a project you need to specify the package and rule that you would like built using a label. e.g.
```
bazel build //path/to/package:rule_name
```
Bazel considers any path beginning with `//` to be an absolute path from the `WORKSPACE` file and will search the `BUILD` file it finds at that location for any rules matching `rule_name`.

## An Example
Suppose we have a project called `foo` with a package called `bar` that contains two files: `hello.c` and `hello.h`. The directory structure of this project would look something like this:
```
/foo
    |
    -- WORKSPACE
    |
    -- /bar
        |
        -- BUILD
        |
        -- hello.c
        |
        -- hello.h
```

Lets say we have a rule called `hello` defined in the `BUILD` file. In order to build the package bar we would call:
```
bazel build //bar:hello
```

## Further Reading
If you want more information about the concepts touched on above please read the bazel documentation:

* [Getting Started with C++](https://docs.bazel.build/versions/master/tutorial/cpp.html)
* [C++ Best Practices](https://docs.bazel.build/versions/master/bazel-and-cpp.html)
* [C++ Use Case Examples](https://docs.bazel.build/versions/master/cpp-use-cases.html)
* [Build Concepts](https://docs.bazel.build/versions/master/build-ref.html)
* [Build Encyclopedia](https://docs.bazel.build/versions/master/be/overview.html)

It is not expected that you read all of the documentation listed above, it is merely placed there for future reference.

