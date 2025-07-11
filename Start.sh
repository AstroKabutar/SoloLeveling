#! /bin/bash

echo "Population files with env variables"
envsubst < templates_raw/index.html > templates/index.html
envsubst < templates_raw/LoadGame.html > templates/LoadGame.html

echo "Deleting the raw templates"
rm -rf templates_raw

echo "Starting node exporter"
./node_exporter --web.listen-address=:6000 > /dev/null 2>&1 &

echo "Starting the application"
./SoloLeveling