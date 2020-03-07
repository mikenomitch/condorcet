
defmodule CondorcetWeb.Api.V1.ErrorView do
  use CondorcetWeb, :view

  def render("error.json", %{error_message: message}) do
    %{error: message}
  end
end
