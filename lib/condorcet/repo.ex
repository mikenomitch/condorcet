defmodule Condorcet.Repo do
  use Ecto.Repo,
    otp_app: :condorcet,
    adapter: Ecto.Adapters.Postgres
end
