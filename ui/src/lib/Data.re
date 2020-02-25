type poll = {
  id: option(string),
  choices: list(string),
  manageToken: option(string),
  question: string,
};

type response = {
  id: option(int),
  name: string,
  order: list(string),
};

type winnerMap = {
  borda: list(string),
  ranked: list(string),
  plurality: list(string),
  condorcet: option(string),
};

type fullResultsMap = {
  borda: Js.Dict.t(int),
  plurality: Js.Dict.t(int),
  ranked: list(list(string)),
};

type result = {
  winners: option(winnerMap),
  fullResults: option(fullResultsMap),
  names: list(string),
  responseCount: int,
  poll,
};

type errorsMap = {
  choices: option(list(string)),
  question: option(list(string)),
};
type errors = {errors: errorsMap};

type pollVariant =
  | PollErrors(errors)
  | PollRes(poll);

type responseVariant =
  | ResponseErrors(errors)
  | ResponseRes(response);

type resultVariant =
  | ResultErrors(errors)
  | ResultRes(result);

// === JSON DECODING ===

module Decode = {
  let dPoll = (json): poll =>
    Json.Decode.{
      id: json |> optional(field("id", string)),
      question: json |> field("question", string),
      choices: json |> field("choices", list(string)),
      manageToken: json |> optional(field("manage_token", string)),
    };

  let dResponse = (json): response =>
    Json.Decode.{
      id: json |> optional(field("id", int)),
      name: json |> field("name", string),
      order: json |> field("order", list(string)),
    };

  let dfullResults = (json): fullResultsMap =>
    Json.Decode.{
      borda: json |> field("borda", dict(int)),
      plurality: json |> field("plurality", dict(int)),
      ranked: json |> field("ranked", list(list(string))),
    };

  let dWinnerMap = (json): winnerMap =>
    Json.Decode.{
      borda: json |> field("borda", list(string)),
      plurality: json |> field("plurality", list(string)),
      ranked: json |> field("ranked", list(string)),
      condorcet: json |> field("condorcet", optional(string)),
    };

  let dResult = (json): result =>
    Json.Decode.{
      poll: json |> field("poll", dPoll),
      winners: json |> optional(field("winners", dWinnerMap)),
      fullResults: json |> optional(field("full_results", dfullResults)),
      responseCount: json |> field("response_count", int),
      names: json |> field("names", list(string)),
    };

  let dErrorsPollMap = (json): errorsMap =>
    Json.Decode.{
      choices: json |> optional(field("choices", list(string))),
      question: json |> optional(field("question", list(string))),
    };

  let dPollErrors = (json): errors =>
    Json.Decode.{errors: json |> field("errors", dErrorsPollMap)};

  let dPollOrErrors =
    Json.Decode.(
      either(
        dPoll |> map(p => PollRes(p)),
        dPollErrors |> map(s => PollErrors(s)),
      )
    );

  // TODO: FIX THE ERRORS OPTION
  let dResponseOrErrors =
    Json.Decode.(
      either(
        dResponse |> map(r => ResponseRes(r)),
        dPollErrors |> map(r => ResponseErrors(r)),
      )
    );

  // TODO: FIX THE ERRORS OPTION
  let dResultOrErrors =
    Json.Decode.(
      either(
        dResult |> map(r => ResultRes(r)),
        dPollErrors |> map(r => ResultErrors(r)),
      )
    );
};

// === JSON ENCODING ===

let encodePoll = (poll: poll) =>
  Json.Encode.object_([
    ("question", Json.Encode.string(poll.question)),
    ("choices", Json.Encode.list(Json.Encode.string, poll.choices)),
  ]);

let encodeResponse = response =>
  Json.Encode.object_([
    ("name", Json.Encode.string(response.name)),
    ("order", Json.Encode.list(Json.Encode.string, response.order)),
  ]);

let encodeChoice = (choice: string) =>
  Json.Encode.object_([("choice", Json.Encode.string(choice))]);

let encodePollPost = poll =>
  Json.Encode.object_([("poll", encodePoll(poll))]);

let encodeResponsePost = poll =>
  Json.Encode.object_([("response", encodeResponse(poll))]);