#! /bin/bash

#envsubst < templates_raw/index.html > templates/index.html


# http://$HTML_IP:$HTML_PORT/"

source runner/bin/activate
pip install flask
python3 mywebsite.py