# Condorcet

## Dependencies

- Elixir
- Postgres
- Node
- Bucklescript `npm install -g bs-platform`
- Parcel `npm install -g parcel-bundler`

## Running the App (Local)

- Change to `./api` directory
- Install dependencies with `mix deps.get`
- Create and migrate your database with `mix ecto.setup`

- Change to `./ui` directory
- `bsb -make-world`
- `npm install`
- `npm run dev`
- `npm run js`

- Change to home directory
- Run `./bin/run.sh`

- Access the app at localhost:4000

## Running the App (Docker)

- Run `./bin/docker_build.sh`
- Run `./bin/docker_run.sh`

- Access the app at localhost:4000
