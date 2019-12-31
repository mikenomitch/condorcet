defmodule Condorcet.Response do
  use Ecto.Schema
  import Ecto.Changeset
  alias Condorcet.{Repo, Poll, Response}

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

  def create_for_poll(poll_id, attrs) do
    Repo.get(Poll, poll_id)
      |> Ecto.build_assoc(:response)
      |> changeset(attrs)
      |> Repo.insert()
  end
end
