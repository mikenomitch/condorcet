defmodule Condorcet.Repo.Migrations.CreateResults do
  use Ecto.Migration

  def change do
    create table(:results) do
      add :winners, :map
      add :full_results, :map
      add :response_count, :integer
      add :poll_id, references(:polls, on_delete: :nothing)

      timestamps()
    end

    create index(:results, [:poll_id])
  end
end
