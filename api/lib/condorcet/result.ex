defmodule Condorcet.Result do
  use Ecto.Schema
  import Ecto.Changeset

  schema "results" do
    field :response_count, :integer
    field :full_results, :map
    field :winners, :map
    field :poll_id, :id

    timestamps()
  end

  @doc false
  def changeset(result, attrs) do
    result
    |> cast(attrs, [:winners, :full_results, :response_count])
    |> validate_required([:winners, :full_results, :response_count])
  end
end
