#!/bin/sh

docker stack rm trashly
docker build -t localhost:5000/trashly .
docker stack deploy -c docker-compose.yml trashly
