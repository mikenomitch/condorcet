defmodule Condorcet.Repo.Migrations.CreateResponses do
  use Ecto.Migration

  def change do
    create table(:responses) do
      add :order, {:array, :string}
      add :name, :string
      add :poll_id, references(:polls, on_delete: :nothing)

      timestamps()
    end

    create index(:responses, [:poll_id])
  end
end
