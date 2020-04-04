defmodule Condorcet.Repo.Migrations.AddPublicResultsToPolls do
  use Ecto.Migration

  def change do
    alter table("polls") do
      add :public_results, :bool, default: true
    end
  end
end
