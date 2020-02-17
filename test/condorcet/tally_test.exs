defmodule Condorcet.TallyTest do
  alias Condorcet.Tally
  use ExUnit.Case

  # =================
  # === PLURALITY ===
  # =================

  test "calculates plurality (single winner)" do
    choices = [
      ["A", "B", "C"],
      ["A", "C", "B"],
      ["B", "A", "C"],
      ["C", "B", "A"]
    ]

    assert Tally.calc_plurality(choices) == ["A"]
  end

  test "calculates plurality (multi winner)" do
    choices = [
      ["A", "B", "C"],
      ["A", "C", "B"],
      ["B", "A", "C"],
      ["B", "C", "A"],
    ]

    assert Tally.calc_plurality(choices) == ["A", "B"]
  end

  # ===================
  # === BORDA COUNT ===
  # ===================

  test "calculates borda (simple)" do
    choices = [
      ["A", "B", "C"],
      ["A", "C", "B"],
      ["B", "A", "C"],
      ["C", "B", "A"]
    ]

    assert Tally.calc_borda(choices) == ["A"]
  end

  test "calculates borda (slightly more complex)" do
    choices = [
      ["A", "D", "C", "B"],
      ["A", "D", "B", "C"],
      ["B", "D", "C", "A"],
      ["C", "D", "B", "A"]
    ]

    assert Tally.calc_borda(choices) == ["D"]
  end

  # =============
  # ==== IRV ====
  # =============

  test "calculates irv (immediate winner)" do
    choices = [
      ["A", "B", "C"],
      ["A", "C", "B"],
      ["A", "B", "C"],
      ["C", "B", "A"]
    ]

    assert Tally.calc_irv(choices) == ["A"]
  end

  test "calculates irv (single elimination)" do
    choices = [
      ["A", "B", "C"],
      ["A", "C", "B"],
      ["B", "A", "C"],
      ["C", "B", "A"]
    ]

    assert Tally.calc_irv(choices) == ["A"]
  end

  test "calculates irv (slightly more complex)" do
    choices = [
      ["A", "D", "C", "B"],
      ["A", "D", "B", "C"],
      ["B", "D", "C", "A"],
      ["B", "D", "C", "A"]
    ]

    assert Tally.calc_irv(choices) == ["A", "B"]
  end

  test "calculates irv (initial tie)" do
    choices = [
      ["A", "B", "C"],
      ["A", "C", "B"],
      ["B", "A", "C"],
      ["B", "A", "C"]
    ]

    assert Tally.calc_irv(choices) == ["A", "B"]
  end

  test "calculates irv (tie after first but not end)" do
    choices = [
      ["A", "B", "C", "D"],
      ["A", "B", "C", "D"],
      ["C", "A", "B", "D"],
      ["B", "A", "C", "D"],
      ["B", "A", "C", "D"],
      ["D", "B", "A", "C"]
    ]

    assert Tally.calc_irv(choices) == ["A", "B"]
  end

  test "calculates irv (three way tie without majority)" do
    choices = [
      ["A", "B", "C"],
      ["A", "B", "C"],
      ["C", "A", "B"],
      ["B", "A", "C"],
      ["B", "A", "C"],
      ["C", "B", "A"]
    ]

    assert Tally.calc_irv(choices) == ["A", "B", "C"]
  end

  test "calculates irv (ends with two way tie)" do
    choices = [
      ["A", "B", "C"],
      ["A", "B", "C"],
      ["A", "B", "C"],
      ["B", "A", "C"],
      ["B", "A", "C"],
      ["B", "A", "C"],
      ["C", "A", "B"],
      ["C", "B", "A"]
    ]

    assert Tally.calc_irv(choices) == ["A", "B"]
  end

  test "calculates irv (initial plurality loses)" do
    choices = [
      ["A", "B", "C", "D"],
      ["A", "B", "C", "D"],
      ["A", "B", "C", "D"],
      ["B", "A", "C", "D"],
      ["B", "A", "C", "D"],
      ["C", "B", "A", "D"],
      ["D", "B", "A", "C"],
    ]

    assert Tally.calc_irv(choices) == ["B"]
  end

  # TODO: figure this one out
  # test "calculates irv (TODO: figure this one out!)" do
  #   choices = [
  #     ["A", "B", "C", "D"],
  #     ["A", "B", "C", "D"],
  #     ["B", "A", "C", "D"],
  #     ["C", "B", "A", "D"],
  #     ["D", "B", "A", "C"],
  #   ]

  #   assert Tally.calc_irv(choices) == ["B"]
  # end

  # ==========================
  # ==== CONDORCET WINNER ====
  # ==========================

  test "calculates simple condorcet winner 1" do
    choices = [
      ["A", "B", "C", "D"],
      ["A", "B", "C", "D"],
      ["B", "A", "C", "D"],
      ["D", "A", "B", "C"],
    ]

    assert Tally.calc_condorcet(choices) == "A"
  end

  test "calculates simple condorcet winner 2" do
    choices = [
      ["A", "B", "C", "D"],
      ["A", "B", "C", "D"],
      ["B", "A", "C", "D"],
      ["D", "B", "A", "C"],
      ["D", "B", "A", "C"],
    ]

    assert Tally.calc_condorcet(choices) == "B"
  end

  test "calculates no condorcet winner 1" do
    choices = [
      ["A", "B", "C", "D"],
      ["A", "B", "C", "D"],
      ["B", "A", "C", "D"],
      ["B", "A", "C", "D"],
    ]

    assert Tally.calc_condorcet(choices) == nil
  end

  test "calculates no condorcet winner 2" do
    choices = [
      ["D", "A", "B", "C"],
      ["B", "C", "A", "D"],
      ["C", "D", "A", "B"],
    ]

    assert Tally.calc_condorcet(choices) == nil
  end
end
