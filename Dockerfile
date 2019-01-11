FROM continuumio/anaconda

WORKDIR /workdir

RUN apt-get update && apt-get install -y \
        gcc make valgrind

RUN apt-get install -y vim
