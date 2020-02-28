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
      |> Ecto.build_assoc(:responses, attrs)
      |> changeset(attrs)

    Multi.new()
      |> Multi.insert(:response, response_cs)
      |> Multi.run(:result, fn (repo, _) ->
        recalc_responses(repo, poll.id)
      end
      )
      |> Repo.transaction()
  end

  def destroy_and_update_result(id) do
    response = Repo.get(Response, id)
    Multi.new()
    |> Multi.run(:response, fn (repo, _) ->
      repo.delete(response)
    end)
    |> Multi.run(:result, fn (repo, _) ->
      with res = %Result{} <- recalc_responses(repo, response.poll_id) do
        {:ok, res}
      else
        error -> error
      end
    end)
    |> Repo.transaction()
  end

  # PRIVATE

 defp recalc_responses(repo, poll_id) do
  query = from(Response, where: [poll_id: ^poll_id])
  responses = repo.all(query)

  result_attrs = %{
    winners: Tally.calc_winners(responses),
    full_results: Tally.full_results(responses),
    response_count: Enum.count(responses)
  }

  Result
  |> repo.get_by(poll_id: poll_id)
  |> Result.changeset(result_attrs)
  |> repo.insert_or_update()
 end
end
