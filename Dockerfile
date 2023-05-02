FROM gcc:latest

RUN apt-get update && apt-get install -y nginx

COPY . /usr/src/ecommerceapp
WORKDIR /usr/src/ecommerceapp

RUN g++ -o ecommerceapp ecommerceapp.cpp

CMD service nginx start && ./ecommerceapp