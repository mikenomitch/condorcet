defmodule CondorcetWeb.Api.V1.PollView do
  use CondorcetWeb, :view

  def render("show.json", %{poll: poll}) do
    render_one(poll, __MODULE__, "poll.json")
  end

  def render("poll.json", %{poll: poll}) do
    %{id: poll.id, question: poll.question, choices: poll.choices}
  end

  def render("results.json", %{poll: poll, result: result}) do
    poll_json = render("poll.json", poll: poll)

    winner = "Jimbob"
    %{poll: poll_json, winner: winner, responseCount: result.response_count}
  end
end
