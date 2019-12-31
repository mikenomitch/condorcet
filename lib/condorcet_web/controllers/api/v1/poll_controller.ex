defmodule CondorcetWeb.Api.V1.PollController do
  alias Condorcet.{Repo, Poll, Result}

  use CondorcetWeb, :controller
  @type conn_t :: Plug.Conn.t()

  @doc false
  def show(conn, %{"id" => id}) do
    poll = Repo.get(Poll, id)
    render(conn, "show.json", poll: poll)
  end

  @doc false
  def create(conn, %{"poll" => params}) do
    with {:ok, %Poll{} = poll} <- Poll.create(params) do
      conn
      |> put_status(:created)
      |> render("show.json", poll: poll)
    end
  end

  @doc false
  def results(conn, %{"poll_id" => id}) do
    poll = Repo.get(Poll, id)
    result = Repo.get_by(Result, poll_id: id) || %Result{response_count: 0}
    render(conn, "results.json", poll: poll, result: result)
  end
end
