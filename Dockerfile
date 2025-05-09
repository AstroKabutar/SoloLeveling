FROM debian:stable-slim

RUN apt-get update &&\
    apt install -y gettext &&\
    apt install -y python3 &&\
    apt install python3.11-venv &&\
    python3 -m venv runner

RUN mkdir /mywebsite
COPY . /mywebsite
WORKDIR /mywebsite

EXPOSE 80

CMD ["bash", "start.sh"]