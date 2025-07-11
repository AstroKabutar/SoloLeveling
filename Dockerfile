FROM schd1337/portfolioapp:baseimage

COPY . /SoloLeveling
RUN chmod 755 -R /SoloLeveling
WORKDIR /SoloLeveling
EXPOSE 80

# Node exporter port
EXPOSE 6000

CMD ["bash", "Start.sh"]