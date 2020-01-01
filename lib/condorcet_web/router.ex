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
      post("/respond", ResponseController, :create)
      resources("/responses", ResponseController)
      get("/results", PollController, :results)
    end
  end

  scope "/", CondorcetWeb do
    pipe_through :browser
    get "/*_anything", PageController, :index
  end
end
