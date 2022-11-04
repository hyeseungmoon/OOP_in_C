FROM gcc:latest
COPY . /usr/src/myapp
WORKDIR /usr/src/myapp

RUN apt-get update -y
RUN apt-get upgrade -y
RUN apt-get install -y cmake

RUN cmake CMakeLists.txt
RUN make

CMD ./DS