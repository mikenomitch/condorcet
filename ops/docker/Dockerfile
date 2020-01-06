# Dockerfile
FROM elixir:1.9.4-alpine

# install build dependencies
RUN apk add --update git bash build-base nodejs npm libssl1.1 openssl python util-linux

# prepare build dir
RUN mkdir /app
WORKDIR /app

# install hex + rebar
RUN mix local.hex --force && mix local.rebar --force

# set build ENV
ENV MIX_ENV=prod
ENV NODE_ENV=production
ENV PARCEL_WORKERS=1

# install mix dependencies
COPY mix.exs mix.lock config ./
RUN mix deps.get
RUN mix deps.compile

# build assets
COPY ui ui
RUN cd ui && npm install -g --unsafe-perm bs-platform
RUN cd ui && npm install -g parcel-bundler --unsafe-perm
RUN cd ui && bsb -make-world
RUN cd ui && npm install
RUN cd ui && npm link bs-platform
RUN cd ui && npm run deploy

# ...I think I only need this for a real build?
# RUN mix phx.digest

COPY ./ ./
EXPOSE 4000

CMD mix phx.server
