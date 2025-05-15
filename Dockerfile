FROM debian:stable-slim

RUN apt-get update &&\
    apt install -y gettext &&\
    apt install -y python3 &&\
    apt install -y python3.11-venv &&\
    apt install gettext -y &&\
    apt install pip -y
    #pip install flask

RUN mkdir /mywebsite
COPY . /mywebsite
WORKDIR /mywebsite

EXPOSE 80

CMD ["bash", "start.sh"]


# docker build -t schd1337/mywebsite:v2 . 
