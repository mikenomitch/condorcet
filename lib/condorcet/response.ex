defmodule Condorcet.Response do
  use Ecto.Schema
  import Ecto.Query
  import Ecto.Changeset
  alias Condorcet.{Repo, Poll, Response, Result, Tally}
  alias Ecto.Multi

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

  def create_for_poll(take_token, attrs) do
    poll = Poll |> Repo.get_by(take_token: take_token)

    response_cs = poll
      |> Ecto.build_assoc(:response, attrs)
      |> changeset(attrs)

    Multi.new()
      |> Multi.insert(:response, response_cs)
      |> Multi.run(:result, fn (repo, _) ->
        query = from(Response, where: [poll_id: ^poll.id])
        responses = Repo.all(query)

        result_attrs = %{
          winners: Tally.calc_winners(poll.id),
          full_results: Tally.full_results(poll.id),
          response_count: Enum.count(responses)
        }

        case repo.get_by(Result, poll_id: poll.id) do
          nil  -> %Result{poll_id: poll.id}
          post -> post
        end
        |> Result.changeset(result_attrs)
        |> repo.insert_or_update()
      end
      )
      |> Repo.transaction()
  end
end
