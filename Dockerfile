FROM schd1337/baseimages:sololeveling AS production

WORKDIR /SoloLeveling
COPY . .
RUN chmod 755 -R /SoloLeveling
EXPOSE 80

# Node exporter port
#EXPOSE 6000

CMD ["bash", "Start.sh"]

# docker build -t schd1337/portfolioapp:latest .
# docker push schd1337/portfolioapp:latest