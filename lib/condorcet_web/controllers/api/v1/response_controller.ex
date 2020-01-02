defmodule CondorcetWeb.Api.V1.ResponseController do
  import Ecto.Query
  alias Condorcet.{Repo, Response}

  use CondorcetWeb, :controller
  @type conn_t :: Plug.Conn.t()

  @spec show(conn_t, map) :: {:error, :not_found} | conn_t
  def show(conn, %{"id" => id}) do
    response = Repo.get(Response, id)
    render(conn, "show.json", response: response)
  end

  @doc false
  def index(conn, %{"poll_id" => poll_id}) do
    query = from(Response, where: [poll_id: ^poll_id])
    responses = Repo.all(query)
    render(conn, "index.json", responses: responses)
  end

  @doc false
  # TODO: this pattern match is bad!
  def create(conn, %{"poll_id" => poll_id, "response" => attrs}) do
    with {:ok, %{response: response}} <- Response.create_for_poll(poll_id, attrs) do
      conn
      |> put_status(:created)
      |> render("show.json", response: response)
    end
  end
end
