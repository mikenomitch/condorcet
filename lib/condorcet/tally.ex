defmodule Condorcet.Tally do
  import Ecto.Query
  alias Condorcet.{Repo, Response}

  def calculate_winners(poll_id) do
    query = from(Response, where: [poll_id: ^poll_id])
    responses = Repo.all(query)

    %{
      "plurality" => calculate_plurality(responses),
      "ranked" => calculate_irv(responses),
      "borda" => calculate_borda(responses),
      "condorcet" => calculate_condorcet(responses)
    }
  end

  def calculate_plurality(responses) do
    first_place_counts = get_first_place_counts(responses)
    highest_vote_count = first_place_counts |> Map.values |> Enum.max
    first_place_counts |> Enum.filter(
      fn ({_, count}) -> count == highest_vote_count end
    ) |> Enum.map(
      fn ({choice, _}) -> choice end
    )
  end

  def calculate_irv(responses) do
    hd(responses).order
  end

  def calculate_borda(responses) do
    example_order = hd(responses).order
    choices_count = Enum.count(example_order)

    responses
    |> Enum.map(&(&1.order))
    |> Enum.reduce(%{},
      fn (choices, outer_counts) ->
        choices
        |> Enum.with_index()
        |> Enum.reduce(outer_counts, fn ({choice, idx}, internal_counts) ->
          add_by = choices_count - idx
          Map.update(internal_counts, choice, add_by, &(&1 + add_by))
        end)
      end
    )
  end

  def calculate_condorcet(responses) do
    hd(responses).order
  end

  # PRIVATE

  defp get_first_place_counts(responses) do
    responses
    |> Enum.map(&(&1.order))
    |> Enum.map(&(hd &1))
    |> Enum.group_by(&(&1))
    |> Enum.reduce(%{},
      fn ({name, list}, acc) ->
        Map.put(acc, name, Enum.count(list))
      end
    )
  end
end
