#! /bin/bash
echo "Restarting pods static website"
kubectl get pods -nstatic | awk 'NR == 2 {print $1}' | xargs kubectl delete pods -nstatic
echo "Restarted"