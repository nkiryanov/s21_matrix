FROM ubuntu:latest

RUN apt-get update && \
    apt-get install -y \
    git make check lcov pkg-config valgrind clang-format cppcheck
COPY .  /code
WORKDIR /code/src

CMD bash
