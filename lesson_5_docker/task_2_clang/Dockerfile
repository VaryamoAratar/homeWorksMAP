FROM ubuntu:latest

RUN apt-get -y update && apt-get install -y

RUN apt-get -y install clang

COPY . /usr/src/sort

WORKDIR /usr/src/sort

RUN clang++ -o Test_sort main.cpp

CMD ["./Test_sort"]