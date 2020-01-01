type poll = {
  id: option(int),
  question: string,
  choices: list(string),
};

type response = {
  id: option(int),
  name: string,
  choices: list(string),
};

type result = {
  winner: string,
  responseCount: int,
  poll,
};

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
      choices: json |> field("choices", list(string)),
    };

  let dResult = (json): result =>
    Json.Decode.{
      poll: json |> field("poll", dPoll),
      winner: json |> field("winner", string),
      responseCount: json |> field("responseCount", int),
    };
};

// === JSON ENCODING ===

let encodePoll = poll =>
  Json.Encode.object_([
    ("question", Json.Encode.string(poll.question)),
    ("choices", Json.Encode.list(Json.Encode.string, poll.choices)),
  ]);

let encodeResponse = response =>
  Json.Encode.object_([
    ("name", Json.Encode.string(response.name)),
    ("choices", Json.Encode.list(Json.Encode.string, response.choices)),
  ]);

let encodeResult = result =>
  Json.Encode.object_([
    ("poll", encodePoll(result.poll)),
    ("winner", Json.Encode.string(result.winner)),
    ("responseCount", Json.Encode.int(result.responseCount)),
  ]);

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

let [_, winner, ..._rest] = examplePoll.choices;
let exampleResult: result = {poll: examplePoll, winner, responseCount: 3};