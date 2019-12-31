defmodule CondorcetWeb.Router do
  use CondorcetWeb, :router

  pipeline :browser do
    plug :accepts, ["html"]
    plug :fetch_session
    plug :fetch_flash
    plug :protect_from_forgery
    plug :put_secure_browser_headers
  end

  pipeline :api do
    plug :accepts, ["json"]
  end

  scope "/api/v1/", CondorcetWeb.Api.V1 do
    pipe_through :api

    resources("/polls", PollController) do
      get("/results", ResultController, :show)
    end
  end

  scope "/", CondorcetWeb do
    pipe_through :browser

    get "/", PageController, :index
  end

  # Other scopes may use custom stacks.
  # scope "/api", CondorcetWeb do
  #   pipe_through :api
  # end
end
