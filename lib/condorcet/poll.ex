defmodule Condorcet.Poll do
  use Ecto.Schema
  import Ecto.Changeset
  alias Condorcet.{Repo, Response}

  schema "polls" do
    field :choices, {:array, :string}
    field :question, :string
    has_one :response, Response

    timestamps()
  end

  @doc false
  def changeset(poll, attrs) do
    poll
    |> cast(attrs, [:question, :choices])
    |> validate_required([:question, :choices])
  end

  def create(attrs) do
    %__MODULE__{}
    |> changeset(attrs)
    |> Repo.insert()
  end
end
