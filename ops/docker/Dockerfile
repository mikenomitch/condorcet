# Dockerfile
FROM elixir:1.9.4-alpine

ENV MIX_HOME=/opt/mix

# install build dependencies
RUN apk add --update git bash build-base nodejs npm libssl1.1 openssl python util-linux wget
RUN wget https://github.com/sgerrand/alpine-pkg-glibc/releases/download/2.23-r3/glibc-2.23-r3.apk && \
  apk add --allow-untrusted glibc-2.23-r3.apk

RUN npm install -g --unsafe-perm bs-platform@7.1.0
RUN npm install -g parcel-bundler --unsafe-perm

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
COPY api/mix.exs api/mix.lock api/config api/
RUN cd api && mix deps.get
RUN cd api && mix deps.compile

# build assets
COPY ui ui
RUN cd ui && npm link bs-platform
RUN cd ui && npm install
RUN cd ui && bsb -make-world
RUN cd ui && npm run build

COPY ./api ./api/
EXPOSE 4000

CMD cd api && mix phx.server
