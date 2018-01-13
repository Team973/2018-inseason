# Installation

Our current bazel setup only provides support for MacOS, Ubuntu, and other Unix style OS', Windows is not supported. As of now only Ubuntu and MacOS are tested.

## Ubuntu-based
Setup the FRC toolchain repo
```
sudo add-apt-repository ppa:wpilib/toolchain
sudo apt-get update
```
Add Bazel distribution URI as a package source
```
echo "deb [arch=amd64] http://storage.googleapis.com/bazel-apt stable jdk1.8" | sudo tee /etc/apt/sources.list.d/bazel.list
curl https://bazel.build/bazel-release.pub.gpg | sudo apt-key add -
sudo apt-get update
```
Install the dependencies
```
sudo apt-get install frc-toolchain openjdk-8-jdk bazel
```
## macOS
Install the FRC toolchain [download here](http://first.wpi.edu/FRC/roborio/toolchains/)

Install java 8 [download here]( http://www.oracle.com/technetwork/java/javase/downloads/jdk8-downloads-2133151.html)

Other dependencies should be installed via [homebrew](https://brew.sh/).
```
brew install bazel
```

# Usage
Build the robot code:
```
bazel build //src:robot --cpu=roborio
```

Build and deploy to the robot:
```
bazel run //tools:deploy --cpu=roborio
```

**Note:** MacOS users need to specify `roborio-darwin` as the cpu
