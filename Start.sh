#! /bin/bash

echo "Population files with env variables"
envsubst < templates_raw/index.html > templates/index.html
envsubst < templates_raw/LoadGame.html > templates/LoadGame.html
envsubst < templates_raw/new_player.html > templates/new_player.html

echo "Deleting the raw templates"
rm -rf templates_raw

echo "Starting the application"
./SoloLeveling