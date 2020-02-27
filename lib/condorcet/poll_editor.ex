defmodule Condorcet.PollEditor do
  import Ecto.Query
  alias Ecto.Multi
  alias Condorcet.{Repo, Poll, Response, Result, Tally}

  def remove_choice_from_poll(orig_poll = %Poll{}, choice) do
    Multi.new()
    |> Multi.run(:poll, fn(repo, _) ->
      new_choices = orig_poll.choices -- [choice]

      new_attrs = %{
        "question" => orig_poll.question,
        "choices" => new_choices,
        "take_token" => orig_poll.take_token,
        "manage_token" => orig_poll.manage_token,
      }

      orig_poll
      |> Poll.update_changeset(new_attrs)
      |> repo.insert_or_update()
    end)
    |> Multi.run(:responses, fn(repo, %{poll: poll}) ->
      query = from(r in Response, where: [poll_id: ^poll.id])
      repo.update_all(query, pull: [order: choice])
      {:ok, repo.all(query)}
    end)
    |> Multi.run(:result, fn(repo, changes) ->
        %{responses: responses, poll: poll} = changes

        result_attrs = %{
          winners: Tally.calc_winners(responses),
          full_results: Tally.full_results(responses),
          response_count: Enum.count(responses)
        }

        Result
        |> repo.get_by(poll_id: poll.id)
        |> Result.changeset(result_attrs)
        |> repo.insert_or_update()
    end)
    |> Repo.transaction()
  end
end
