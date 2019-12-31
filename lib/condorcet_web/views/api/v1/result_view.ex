defmodule CondorcetWeb.Api.V1.ResultView do
  use CondorcetWeb, :view

  def render("show.json", %{result: result, poll: poll}) do
    poll_json = CondorcetWeb.Api.V1.PollView.render("show.json", poll: poll)

    winner = "Jimbob"
    %{poll: poll_json, winner: winner, responseCount: result.response_count}
  end
end
