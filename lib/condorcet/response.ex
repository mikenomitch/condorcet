defmodule Condorcet.Response do
  use Ecto.Schema
  import Ecto.Changeset

  schema "responses" do
    field :name, :string
    field :order, {:array, :string}
    field :poll_id, :id

    timestamps()
  end

  @doc false
  def changeset(response, attrs) do
    response
    |> cast(attrs, [:order, :name])
    |> validate_required([:order, :name])
  end
end
