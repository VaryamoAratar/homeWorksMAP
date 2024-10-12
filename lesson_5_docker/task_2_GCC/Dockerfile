FROM gcc:latest

COPY . /usr/src/sort_test
WORKDIR /usr/src/sort_test

RUN g++ -o sort_test main.cpp

CMD ["./sort_test"]

LABEL Name=task2gcc Version=0.0.1
