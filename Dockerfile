FROM ubuntu:artful

RUN apt-get update
RUN apt-get install -y software-properties-common python-software-properties curl libc6-i386

RUN add-apt-repository ppa:wpilib/toolchain

RUN echo "deb [arch=amd64] http://storage.googleapis.com/bazel-apt stable jdk1.8" | tee /etc/apt/sources.list.d/bazel.list
RUN curl https://bazel.build/bazel-release.pub.gpg | apt-key add -

RUN apt-get update

RUN apt-get install -y frc-toolchain bazel openjdk-8-jdk git clang

ADD . /build

WORKDIR /build
