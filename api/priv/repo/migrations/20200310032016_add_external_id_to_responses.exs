defmodule Condorcet.Repo.Migrations.AddExternalIdToResponses do
  use Ecto.Migration

  def change do
    alter table("responses") do
      add :external_id, :uuid
    end

    create unique_index(:responses, [:external_id])
  end
end
