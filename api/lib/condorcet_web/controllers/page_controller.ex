defmodule CondorcetWeb.PageController do
  use CondorcetWeb, :controller

  def index(conn, _params) do
    render(conn, "index.html")
  end
end
