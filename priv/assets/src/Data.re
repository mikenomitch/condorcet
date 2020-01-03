type poll = {
  id: option(int),
  question: string,
  choices: list(string),
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
};

type result = {
  winners: option(winnerMap),
  responseCount: int,
  poll,
};

type errorsMap = {
  choices: option(list(string)),
  question: option(list(string)),
};

type errors = {errors: errorsMap};

type pollVariant =
  | Errors(errors)
  | Poll(poll);

// === JSON DECODING ===

module Decode = {
  let dPoll = (json): poll =>
    Json.Decode.{
      id: json |> optional(field("id", int)),
      question: json |> field("question", string),
      choices: json |> field("choices", list(string)),
    };

  let dResponse = (json): response =>
    Json.Decode.{
      id: json |> optional(field("id", int)),
      name: json |> field("name", string),
      order: json |> field("order", list(string)),
    };

  let dWinnerMap = (json): winnerMap =>
    Json.Decode.{
      borda: json |> field("borda", list(string)),
      plurality: json |> field("plurality", list(string)),
      ranked: json |> field("ranked", list(string)),
    };

  let dResult = (json): result =>
    Json.Decode.{
      poll: json |> field("poll", dPoll),
      winners: json |> optional(field("winners", dWinnerMap)),
      responseCount: json |> field("responseCount", int),
    };

  let dErrorsMap = (json): errorsMap =>
    Json.Decode.{
      choices: json |> optional(field("choices", list(string))),
      question: json |> optional(field("questions", list(string))),
    };

  let dErrors = (json): errors =>
    Json.Decode.{errors: json |> field("errors", dErrorsMap)};

  let dPollOrErrors =
    Json.Decode.(
      either(dPoll |> map(p => Poll(p)), dErrors |> map(s => Errors(s)))
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

let encodePollPost = poll =>
  Json.Encode.object_([("poll", encodePoll(poll))]);

let encodeResponsePost = poll =>
  Json.Encode.object_([("response", encodeResponse(poll))]);

// === EXAMPLE DATA ===

let examplePoll: poll = {
  id: Some(1),
  question: "what is best in life?",
  choices: [
    "to crush your enemies",
    "to see your enemies driven before you",
    "to hear the lamentations of their women",
  ],
};