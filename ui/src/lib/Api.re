[@bs.val] external alert: string => unit = "alert";

let protocol = Constants.protocol;
let host = Constants.host;

let baseUrl = protocol ++ "://" ++ host;

let fetchPoll = (id, cb) => {
  let callCb = (poll: Data.poll) => {
    cb(_ => Some(poll));
  };

  Js.Promise.(
    Fetch.fetch(baseUrl ++ "/api/v1/polls/" ++ id)
    |> then_(Fetch.Response.json)
    |> then_(json => json |> Data.Decode.dPoll |> callCb |> resolve)
    |> ignore
  );
};

let fetchResult = (id, cb) => {
  let callCb = (result: Data.result) => {
    cb(_ => Some(result));
  };

  Js.Promise.(
    Fetch.fetch(baseUrl ++ "/api/v1/polls/" ++ id ++ "/results")
    |> then_(Fetch.Response.json)
    |> then_(json => json |> Data.Decode.dResult |> callCb |> resolve)
    |> ignore
  );
};

let fetchManageResult = (manageToken, cb) => {
  let callCb = (result: Data.result) => {
    cb(_ => Some(result));
  };

  Js.Promise.(
    Fetch.fetch(baseUrl ++ "/api/v1/polls/" ++ manageToken ++ "/manage")
    |> then_(Fetch.Response.json)
    |> then_(json => json |> Data.Decode.dResult |> callCb |> resolve)
    |> ignore
  );
};

let createPoll = (poll, addError) => {
  let payload = Data.encodePollPost(poll);
  Js.Promise.(
    Fetch.fetchWithInit(
      baseUrl ++ "/api/v1/polls/",
      Fetch.RequestInit.make(
        ~method_=Post,
        ~body=Fetch.BodyInit.make(Js.Json.stringify(payload)),
        ~headers=Fetch.HeadersInit.make({"Content-Type": "application/json"}),
        (),
      ),
    )
    |> then_(Fetch.Response.json)
    |> then_(json => {
         switch (Data.Decode.dPollOrErrors(json)) {
         | PollErrors(errors) =>
           let questionErrors =
             switch (errors.errors.question) {
             | Some(errorList) => errorList |> List.map(s => "Question " ++ s)
             | _ => []
             };

           let choiceErrors =
             switch (errors.errors.choices) {
             | Some(errorList) => errorList
             | _ => []
             };

           let showErrors =
             choiceErrors
             @ questionErrors
             |> Array.of_list
             |> Js.Array.joinWith(", ");

           addError("error", showErrors);
           resolve(None);
         | PollRes(poll) => resolve(Some(poll))
         }
       })
  );
};

let submitPoll = (id, response) => {
  let payload = Data.encodeResponsePost(response);
  Js.Promise.(
    Fetch.fetchWithInit(
      baseUrl ++ "/api/v1/polls/" ++ id ++ "/respond",
      Fetch.RequestInit.make(
        ~method_=Post,
        ~body=Fetch.BodyInit.make(Js.Json.stringify(payload)),
        ~headers=Fetch.HeadersInit.make({"Content-Type": "application/json"}),
        (),
      ),
    )
    |> then_(Fetch.Response.json)
    |> then_(json => Data.Decode.dResponseOrErrors(json) |> resolve)
  );
} /* }*/;

let removeChoice = (manageToken, choice) => {
  let payload = Data.encodeChoice(choice);
  Js.Promise.(
    Fetch.fetchWithInit(
      baseUrl ++ "/api/v1/polls/" ++ manageToken ++ "/remove_choice",
      Fetch.RequestInit.make(
        ~method_=Post,
        ~body=Fetch.BodyInit.make(Js.Json.stringify(payload)),
        ~headers=Fetch.HeadersInit.make({"Content-Type": "application/json"}),
        (),
      ),
    )
    |> then_(Fetch.Response.json)
    |> then_(json => Data.Decode.dResultOrErrors(json) |> resolve)
  );
};

let destroyResponse = (manageToken, responseId) => {
  let url =
    baseUrl
    ++ "/api/v1/polls/"
    ++ manageToken
    ++ "/remove_response/"
    ++ responseId;

  Js.Promise.(
    Fetch.fetchWithInit(
      url,
      Fetch.RequestInit.make(
        ~method_=Delete,
        ~headers=Fetch.HeadersInit.make({"Content-Type": "application/json"}),
        (),
      ),
    )
    |> then_(res => res |> resolve)
  );
};