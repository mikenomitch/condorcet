defmodule CondorcetWeb.LayoutView do
  use CondorcetWeb, :view

  def host do
    System.get_env("HOST") || "localhost:4000"
  end

  def protocol do
    System.get_env("PROTOCOL") || "http"
  end
end
