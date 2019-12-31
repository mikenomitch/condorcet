defmodule CondorcetWeb.Api.V1.PollController do
  alias Condorcet.{Poll}

  use CondorcetWeb, :controller
  @type conn_t :: Plug.Conn.t()

  @spec show(conn_t, map) :: {:error, :not_found} | conn_t
  def show(conn, %{"id" => id}) do
    IO.puts("TEST - Poll")

    poll = %Poll{id: id, question: "What is this?", choices: ["1", "2", "3"]}
    render(conn, "show.json", poll: poll)
  end

  def create(conn, %{"poll" => poll_params}) do
    IO.puts(poll_params)
    %{question: question, choices: choices} = poll_params

    with poll <- %Poll{id: 2, question: question, choices: choices} do
      conn
      |> put_status(:created)
      |> render("show.json", poll: poll)
    end
  end
end
