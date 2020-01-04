defmodule CondorcetWeb.Api.V1.PollController do
  alias Condorcet.{Repo, Poll, Result}

  use CondorcetWeb, :controller
  @type conn_t :: Plug.Conn.t()

  @doc false
  def show(conn, %{"id" => id}) do
    poll = Repo.get_by(Poll, take_token: id)
    render(conn, "show.json", poll: poll)
  end

  @doc false
  def create(conn, %{"poll" => params}) do
    with {:ok, %Poll{} = poll} <- Poll.create(params) do
      conn
      |> put_status(:created)
      |> render("manage.json", poll: poll)
    end
  end

  @doc false
  def results(conn, %{"poll_id" => poll_token}) do
    poll = Repo.get_by(Poll, take_token: poll_token)
    result = Repo.get_by(Result, poll_id: poll.id) || %Result{response_count: 0}
    render(conn, "results.json", poll: poll, result: result)
  end

  @doc false
  def manage_results(conn, %{"poll_id" => manage_token}) do
    poll = Repo.get_by(Poll, manage_token: manage_token)
    result = Repo.get_by(Result, poll_id: poll.id) || %Result{response_count: 0}
    render(conn, "manage_results.json", poll: poll, result: result)
  end
end
