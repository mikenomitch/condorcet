defmodule Condorcet.Poll do
  use Ecto.Schema
  import Ecto.Changeset

  schema "polls" do
    field :choices, {:array, :string}
    field :question, :string

    timestamps()
  end

  @doc false
  def changeset(poll, attrs) do
    poll
    |> cast(attrs, [:question, :choices])
    |> validate_required([:question, :choices])
  end
end
