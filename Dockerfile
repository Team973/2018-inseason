FROM ubuntu:xenial

RUN apt -qq update
RUN apt install -y -qq software-properties-common python-software-properties curl libc6-i386

RUN add-apt-repository ppa:wpilib/toolchain

RUN apt install -y -qq openjdk-8-jdk
RUN echo "deb [arch=amd64] http://storage.googleapis.com/bazel-apt stable jdk1.8" | tee /etc/apt/sources.list.d/bazel.list
RUN curl https://bazel.build/bazel-release.pub.gpg | apt-key add -

RUN apt update -qq

RUN apt install -y -qq frc-toolchain bazel git clang

ADD . /build

WORKDIR /build
