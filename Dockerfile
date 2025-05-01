FROM debian:stable-slim

RUN apt-get update &&\
    apt install libmysqlcppconn-dev gettext -y

COPY . /SoloLeveling
RUN chmod 755 -R /SoloLeveling
WORKDIR /SoloLeveling
EXPOSE 80
CMD ["bash", "Start.sh"]

# docker build -t schd1337/portfolioapp:v2 .