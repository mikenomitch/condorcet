defmodule CondorcetWeb.Api.V1.PollView do
  use CondorcetWeb, :view

  def render("show.json", %{poll: poll}) do
    render_one(poll, __MODULE__, "poll.json")
  end

  def render("manage.json", %{poll: poll}) do
    %{
      id: poll.take_token,
      question: poll.question,
      choices: poll.choices,
      manage_token: poll.manage_token
    }
  end

  def render("poll.json", %{poll: poll}) do
    %{
      id: poll.take_token,
      question: poll.question,
      choices: poll.choices
    }
  end

  def render("results.json", %{poll: poll, result: result, responses: responses}) do
    poll_json = render("poll.json", poll: poll)
    names = responses |> Enum.map(&(&1.name))

    %{
      poll: poll_json,
      winners: result.winners,
      full_results: result.full_results,
      response_count: result.response_count,
      names: names
    }
  end

  def render("manage_results.json", %{poll: poll, result: result, responses: responses}) do
    names = responses |> Enum.map(&(&1.name))
    poll_json = render("manage.json", poll: poll)

    %{
      poll: poll_json,
      winners: result.winners,
      full_results: result.full_results,
      response_count: result.response_count,
      names: names
    }
  end
end
