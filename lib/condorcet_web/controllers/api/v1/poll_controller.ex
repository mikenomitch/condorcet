defmodule CondorcetWeb.Api.V1.PollController do
  import Ecto.Query
  alias Condorcet.{Repo, Poll, Result, Response, PollEditor}

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
    query = from(Response, where: [poll_id: ^poll.id])
    responses = Repo.all(query) || []

    render(conn,
      "results.json",
      poll: poll,
      result: result,
      responses: responses
    )
  end

  @doc false
  def manage_results(conn, %{"poll_id" => manage_token}) do
    poll = Repo.get_by(Poll, manage_token: manage_token)
    result = Repo.get_by(Result, poll_id: poll.id) || %Result{response_count: 0}

    query = from(Response, where: [poll_id: ^poll.id])
    responses = Repo.all(query) || []

    render(conn,
      "manage_results.json",
      poll: poll,
      result: result,
      responses: responses
    )
  end

  @doc false
  def remove_choice(conn, %{"poll_id" => manage_token, "choice" => choice}) do
    orig_poll = Repo.get_by(Poll, manage_token: manage_token)

    {:ok,
      %{
        poll: poll,
        result: result,
        responses: responses
      }
    } = PollEditor.remove_choice_from_poll(orig_poll, choice)

    render(conn,
      "manage_results.json",
      poll: poll,
      result: result,
      responses: responses
    )
  end

  def remove_response(conn, %{"poll_id" => manage_token, "response_id" => response_id}) do
    with {:ok, _changes} <- PollEditor.remove_response_from_poll(response_id) do
      send_resp(conn, :no_content, "")
    else
      {:error, _, error, _} -> {:error, error}
      other -> other
    end
  end
end
