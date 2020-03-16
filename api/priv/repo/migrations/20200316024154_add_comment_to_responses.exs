defmodule Condorcet.Repo.Migrations.AddCommentToResponses do
  use Ecto.Migration

  def change do
    alter table("responses") do
      add :comment, :text
    end
  end
end
