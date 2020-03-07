defmodule CondorcetWeb.Api.V1.FallbackController do
  use CondorcetWeb, :controller
  alias CondorcetWeb.{ChangesetView, Api.V1.ErrorView}

  @bad_data_message "There was an issue with your request."
  @not_found_message "Resource Not Found"
  @unauthorized_message "You are not authorized to access this resource."

  # ============
  #   BAD DATA
  # ============

  def call(conn, {:error, %Ecto.Changeset{} = changeset}) do
    conn
    |> put_status(:unprocessable_entity)
    |> render(ChangesetView, "error.json", changeset: changeset)
  end

  def call(conn, {:error, :unprocessable_entity}) do
    call(conn, {:error, :unprocessable_entity, @bad_data_message})
  end

  def call(conn, {:error, :unprocessable_entity, message}) do
    conn
    |> put_status(:unprocessable_entity)
    |> render(ErrorView, "error.json", error_message: message)
  end

  # =============
  #   NOT FOUND
  # =============

  def call(conn, {:error, :not_found}) do
    call(conn, {:error, :not_found, @not_found_message})
  end

  def call(conn, {:error, :not_found, message}) do
    conn
    |> put_status(:not_found)
    |> render(ErrorView, "error.json", error_message: message)
  end

  # ================
  #   UNAUTHORIZED
  # ================

  def call(conn, {:error, :unauthorized}) do
    call(conn, {:error, :unauthorized, @unauthorized_message})
  end

  def call(conn, {:error, :unauthorized, message}) do
    conn
    |> put_status(:forbidden)
    |> render(ErrorView, "error.json", error_message: message)
  end
end
