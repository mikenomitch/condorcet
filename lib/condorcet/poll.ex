defmodule Condorcet.Poll do
  use Ecto.Schema
  import Ecto.Changeset
  alias Condorcet.{Repo, Response}

  schema "polls" do
    field :choices, {:array, :string}
    field :question, :string
    field :take_token, :string
    field :manage_token, :string
    has_one :response, Response

    timestamps()
  end

  @doc false
  def changeset(poll, attrs) do
    poll
    |> cast(attrs, [:question, :choices, :take_token, :manage_token])
    |> validate_choices_not_blank()
    |> validate_choices_not_same()
    |> validate_required([:question, :choices, :take_token, :manage_token])
  end

  def create_changeset(poll, attrs) do
    create_attrs = Map.merge(attrs, %{
      "take_token" => random_string(10),
      "manage_token" => random_string(10)
    })

    changeset(poll, create_attrs)
  end

  def create(attrs) do
    %__MODULE__{}
    |> create_changeset(attrs)
    |> Repo.insert()
  end

  # PRIVATE

  defp random_string(length) do
    :crypto.strong_rand_bytes(length)
    |> Base.url_encode64
    |> binary_part(0, length)
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

  defp validate_choices_not_same(changeset) do
    %{changes: %{choices: choices}} = changeset
    validate_change(changeset, :choices, fn (_, _) ->
      if Enum.uniq(choices) == choices do
        []
      else
        [{:choices, "Multiple choices cannot be the same"}]
      end
    end)
  end
end
