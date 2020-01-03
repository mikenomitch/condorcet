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
    |> validate_choices_not_blank()
    |> validate_required([:question, :choices])
  end

  def create(attrs) do
    %__MODULE__{}
    |> changeset(attrs)
    |> Repo.insert()
  end

  defp validate_choices_not_blank(changeset) do
    %{changes: %{choices: choices}} = changeset
    validate_change(changeset, :choices, fn (_, _) ->
      valid = Enum.all?(choices, &(String.strip(&1) != "" ))
      if valid do
        []
      else
        [{:choices, "Choice cannot be blank"}]
      end
    end)
  end
end
