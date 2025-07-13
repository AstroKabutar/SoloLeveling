FROM schd1337/baseimages:staticwebsite AS production

RUN mkdir /mywebsite
COPY . /mywebsite
WORKDIR /mywebsite

EXPOSE 80

CMD ["bash", "start.sh"]


# docker build -t schd1337/mywebsite:latest . 
