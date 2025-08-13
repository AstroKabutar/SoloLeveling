#! /bin/bash
echo "Restarting pod SoloLeveling"
kubectl get pods -nsololeveling | awk 'NR == 2 {print $1}' | xargs kubectl delete pods -nsololeveling
echo "Restarted"