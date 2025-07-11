FROM debian:stable-slim

RUN apt-get update &&\
    apt-get upgrade -y &&\
    apt install libmysqlcppconn-dev gettext libc6 libstdc++6 -y

COPY . /SoloLeveling
RUN chmod 755 -R /SoloLeveling
WORKDIR /SoloLeveling
EXPOSE 80

# Node exporter port
EXPOSE 6000

CMD ["bash", "Start.sh"]

# docker build -t schd1337/portfolioapp:v3 .