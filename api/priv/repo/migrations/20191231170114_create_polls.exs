defmodule Condorcet.Repo.Migrations.CreatePolls do
  use Ecto.Migration

  def change do
    create table(:polls) do
      add :question, :string
      add :choices, {:array, :string}
      add :manage_token, :string
      add :take_token, :string

      timestamps()
    end
  end
end
