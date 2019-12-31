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
    highest_vote_count = get_highest_vote_count(responses)
    get_choices_with_count(first_place_counts, highest_vote_count)

    first_place_counts |> Enum.filter(
      fn ({_, count}) -> count == highest_vote_count end
    ) |> Enum.map(
      fn ({choice, _}) -> choice end
    )
  end

  def calculate_borda(responses) do
    choices_count = get_choices_count(responses)

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

  # TODO: THIS IS WRONG
  def calculate_irv(responses) do
    hd(responses).order
    # choices_count = get_choices_count(responses)
    # first_place_counts = get_first_place_counts(responses)
    # highest_vote_count = get_highest_vote_count(responses)
    # needed_to_win = ((choices_count / 2) + 1) |> Float.floor()

    # if highest_vote_count >= needed_to_win do
    #   get_choices_with_count(first_place_counts, highest_vote_count)
    # else
    #   if Enum.count(first_place_counts) == Enum.count(responses) do
    #     # return them all since there is no way to break the tie
    #     get_choices_with_count(first_place_counts, highest_vote_count)
    #   end
    #     # run it again without the worst option
    #     responses
    #     |> remove_fewest_first_place_votes()
    #     |> calculate_irv()
    # end
  end

  def calculate_condorcet(responses) do
    hd(responses).order
  end

  # PRIVATE

  # TODO: FIGURE THIS OUT - PSEUDO CODE IT FIRST
  # def do_calculate_irv(orders_list, first_place_votes_to_win) do
  #   orders_list
  #   # TODO
  # end

  def remove_fewest_first_place_votes(responses) do
    first_place_counts = get_first_place_counts(responses)
    lowest_vote_count = get_lowest_vote_count(responses)

    first_place_counts |> Enum.filter(
      fn ({_, count}) -> count != lowest_vote_count end
    ) |> Enum.map(fn ({choice, _}) -> choice end)
  end

  def get_choices_with_count(choices_with_counts, count_to_get) do
    choices_with_counts |> Enum.filter(
      fn ({_, count}) -> count == count_to_get end
    ) |> Enum.map(fn ({choice, _}) -> choice end)
  end

  def get_choices_count(responses) do
    hd(responses).order |> Enum.count()
  end

  def get_highest_vote_count(responses) do
    responses
    |> get_first_place_counts()
    |> Map.values
    |> Enum.max
  end

  def get_lowest_vote_count(responses) do
    responses
    |> get_first_place_counts()
    |> Map.values
    |> Enum.min
  end

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
