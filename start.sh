#! /bin/bash

envsubst < htmls_raw/index.html > htmls/index.html
rm -r htmls_raw
 
python3 -m venv runner
source runner/bin/activate
python3 mywebsite.py