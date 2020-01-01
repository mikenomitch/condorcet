defmodule Condorcet.Tally do
  import Ecto.Query
  alias Condorcet.{Repo, Response}

  def calc_winners(poll_id) do
    query = from(Response, where: [poll_id: ^poll_id])
    responses = Repo.all(query)
    choices = responses |> Enum.map(&(&1.order))

    %{
      "plurality" => calc_plurality(choices),
      "ranked" => calc_irv(choices),
      "borda" => calc_borda(choices)
      # "condorcet" => calc_condorcet(choices)
    }
  end

  def calc_plurality(choices) do
    first_place_counts_by_choice = get_first_place_counts_by_choice(choices)
    highest_vote_count = get_count_of_votes_for_winner(choices)
    get_choices_with_count(first_place_counts_by_choice, highest_vote_count)
  end

  def calc_borda(choices) do
    choices_with_numbers = get_borda_count_numbers(choices)

    max_count = choices_with_numbers
      |> Enum.map(fn ({_, v}) -> v end)
      |> Enum.max

    choices_with_numbers |> Enum.filter(
      fn ({_, v}) -> v == max_count end
    ) |> Enum.map(
      fn ({k, _}) -> k end
    )
  end

  def calc_irv(choices) do
    choices_count = get_choices_count(choices)
    needed_to_win = ((choices_count / 2) + 1) |> Float.floor()
    do_calc_irv(choices, needed_to_win)
  end

  # TODO:
  # In this implementation, all votes with equal lowest 1st place votes
  # are eliminated
  # There should probably be a version of this that just eliminates
  # things one by one by some other method, so it can differentiate
  # between "equally" bad options that are really different
  def do_calc_irv(choices, votes_needed_to_win) do
    first_place_counts_by_choice = get_first_place_counts_by_choice(choices)
    highest_vote_count = get_count_of_votes_for_winner(choices)
    has_enough_votes = highest_vote_count >= votes_needed_to_win
    plurality_winners = get_choices_with_count(first_place_counts_by_choice, highest_vote_count)
    all_winners_are_equal = Enum.count(plurality_winners) == Enum.count(hd choices)

    if (has_enough_votes || all_winners_are_equal) do
      # return the plurality
      plurality_winners
    else
      choices_without_lowest = remove_fewest_first_place_votes(choices)
      do_calc_irv(choices_without_lowest, votes_needed_to_win)
    end
  end

  # PRIVATE

  def get_borda_count_numbers(choices) do
    choices_count = Enum.count(choices)

    choices
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

  def remove_fewest_first_place_votes(choices) do
    first_place_counts_by_choice = get_first_place_counts_by_choice(choices)
    lowest_vote_count = get_lowest_vote_count(choices)

    values_to_remove = first_place_counts_by_choice
      |> Enum.filter(fn ({_, count}) -> count == lowest_vote_count end)
      |> Enum.map(fn ({choice, _}) -> choice end)

    Enum.map(choices, fn (order) ->
      Enum.filter(order, fn(i) ->
        i not in values_to_remove
      end)
    end)
  end

  def get_choices_with_count(choices_with_counts, count_to_get) do
    choices_with_counts |> Enum.filter(
      fn ({_, count}) -> count == count_to_get end
    ) |> Enum.map(fn ({choice, _}) -> choice end)
  end

  def get_choices_count(choices) do
    choices |> Enum.count()
  end

  def get_count_of_votes_for_winner(choices) do
    choices
    |> get_first_place_counts_by_choice()
    |> Map.values
    |> Enum.max
  end

  def get_lowest_vote_count(choices) do
    choices
    |> get_first_place_counts_by_choice()
    |> Map.values
    |> Enum.min
  end

  def get_first_place_counts_by_choice(choices) do
    initial_map = choices |> hd |> Enum.reduce(%{}, fn(choice, acc) ->
      Map.put(acc, choice, 0)
    end)

    choices
    |> Enum.map(&(hd &1))
    |> Enum.group_by(&(&1))
    |> Enum.reduce(initial_map,
      fn ({name, list}, acc) ->
        Map.put(acc, name, Enum.count(list))
      end
    )
  end
end
