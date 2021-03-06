docker run --env PORT=4000 \
  --env HOST=localhost:4000 \
  --env NODE_ENV=production \
  --env PROTOCOL=http \
  --env DATABASE_URL=postgresql://postgres:postgres@host.docker.internal/condorcet \
  --env SECRET_KEY_BASE=9bhPzyt2a7QLFKecq0o8YTlKtpMk77Q4Sg1FxOZzGCao/+HZ4Eos637DGK0M4m2K \
  -it -p 4000:4000 --rm gcr.io/condorcet/app:latest
