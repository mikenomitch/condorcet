# Condorcet/Poller.io

This is the code for [Poller.io](https://poller.io). Poller allows groups to make better decisions using ranked choice voting and alternative election schemes. Results are tallied for Instant Runoff Voting, Borda Counts, the Condorcet Method, and Plurality elections.

The application is written using Elixir and ReasonML. It is hosted on GCP.

For more information on Ranked Choice Voting, check out [CGP Grey's video series](https://www.cgpgrey.com/politics-in-the-animal-kingdom) on the topic.

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
