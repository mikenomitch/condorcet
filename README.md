# Condorcet

# Dependencies

- Elixir
- Postgres
- Node
- Bucklescript `npm install -g bs-platform`
- Parcel `npm install -g parcel-bundler`

# Running the App (Local)

- Install dependencies with `mix deps.get`
- Create and migrate your database with `mix ecto.setup`
- Change to `./ui` directory
- `bsb -make-world`
- `npm install`
- `npm run dev`
- `npm run js`
- Change to home dir
- `iex -S mix phx.server`

# Running the App (Docker)

- Run ./bin/docker_build.sh
- Run ./bin/docker_dun.sh
- Access the app at localhost:4000

# Running the App (Docker)

To start your Phoenix server:

- Install dependencies with `mix deps.get`
- Create and migrate your database with `mix ecto.setup`
- Start Phoenix endpoint with `mix phx.server`
