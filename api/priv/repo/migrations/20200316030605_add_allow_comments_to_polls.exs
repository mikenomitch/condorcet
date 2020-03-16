defmodule Condorcet.Repo.Migrations.AddAllowCommentsToPolls do
  use Ecto.Migration

  def change do
    alter table("polls") do
      add :allow_comments, :bool, default: false
    end
  end
end
