[@bs.val] external alert: string => unit = "alert";

let fetchPoll = (id, cb) => {
  let callCb = (poll: Data.poll) => {
    cb(_ => Some(poll));
  };

  Js.Promise.(
    Fetch.fetch("http://localhost:4000/api/v1/polls/" ++ id)
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
    Fetch.fetch("http://localhost:4000/api/v1/polls/" ++ id ++ "/results")
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
    Fetch.fetch(
      "http://localhost:4000/api/v1/polls/" ++ manageToken ++ "/manage",
    )
    |> then_(Fetch.Response.json)
    |> then_(json => json |> Data.Decode.dResult |> callCb |> resolve)
    |> ignore
  );
};

let createPoll = poll => {
  let payload = Data.encodePollPost(poll);
  Js.Promise.(
    Fetch.fetchWithInit(
      "http://localhost:4000/api/v1/polls/",
      Fetch.RequestInit.make(
        ~method_=Post,
        ~body=Fetch.BodyInit.make(Js.Json.stringify(payload)),
        ~headers=Fetch.HeadersInit.make({"Content-Type": "application/json"}),
        (),
      ),
    )
    //    })
    |> then_(Fetch.Response.json)
    |> then_(json => {
         switch (Data.Decode.dPollOrErrors(json)) {
         | Errors(errors) =>
           let choiceErrors =
             switch (errors.errors.choices) {
             | Some(errorList) => errorList
             | _ => []
             };

           let questionErrors =
             switch (errors.errors.question) {
             | Some(errorList) => errorList
             | _ => []
             };

           let showErrors =
             choiceErrors
             @ questionErrors
             |> Array.of_list
             |> Js.Array.joinWith(", ");

           alert(showErrors);
           resolve(None);

         | Poll(poll) => resolve(Some(poll))
         }
       })
  );
};

let submitPoll = (id, response) => {
  let payload = Data.encodeResponsePost(response);
  Js.Promise.(
    Fetch.fetchWithInit(
      "http://localhost:4000/api/v1/polls/" ++ id ++ "/respond",
      Fetch.RequestInit.make(
        ~method_=Post,
        ~body=Fetch.BodyInit.make(Js.Json.stringify(payload)),
        ~headers=Fetch.HeadersInit.make({"Content-Type": "application/json"}),
        (),
      ),
    )
    |> then_(Fetch.Response.json)
  );
};