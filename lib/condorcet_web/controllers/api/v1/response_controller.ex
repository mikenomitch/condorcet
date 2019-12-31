defmodule CondorcetWeb.Api.V1.ResponseController do
  alias Condorcet.{Poll, Result}

  use CondorcetWeb, :controller
  @type conn_t :: Plug.Conn.t()

  @spec show(conn_t, map) :: {:error, :not_found} | conn_t
  def show(conn, %{"poll_id" => poll_id}) do
    IO.puts("TEST - Response")

    poll = %Poll{id: poll_id, question: "What is this?", choices: ["1", "2", "3"]}
    result = %Result{winners: %{}, response_count: 10}
    render(conn, "show.json", result: result)
  end
end
