defmodule CondorcetWeb.Api.V1.ResponseView do
  use CondorcetWeb, :view

  def render("show.json", %{response: response}) do
    render_one(response, __MODULE__, "response.json")
  end

  def render("response.json", %{response: response}) do
    %{id: response.id, order: response.order}
  end
end
