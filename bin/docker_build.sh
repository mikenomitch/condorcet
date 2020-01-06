echo === BUILD API IMAGE ===
docker build -t mnomitch/condorcet  -f ./ops/docker/Dockerfile ./
echo === DONE BUILDING mnomitch/condorcet ===

# echo === PUSH API TO DOCKERHUB ===
# docker push mnomitch/condorcet