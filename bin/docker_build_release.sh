echo === BUILD IMAGE ===

docker build -t gcr.io/condorcet/app:latest  -f ./ops/docker/Dockerfile ./

echo === DONE BUILDING condorcet/app ===
