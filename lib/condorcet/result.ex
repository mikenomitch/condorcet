defmodule Condorcet.Result do
  use Ecto.Schema
  import Ecto.Changeset

  schema "results" do
    field :response_count, :integer
    field :winners, :map
    field :poll_id, :id

    timestamps()
  end

  @doc false
  def changeset(result, attrs) do
    result
    |> cast(attrs, [:winners, :response_count])
    |> validate_required([:winners, :response_count])
  end

  def create() do

  end
end
