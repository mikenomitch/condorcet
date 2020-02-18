defmodule Condorcet.Repo.Migrations.AddFullResultsToResults do
  use Ecto.Migration

  def change do
    alter table("results") do
      add :full_results, :map
    end
  end
end
