[@react.component]
let make = (~notify, ~result: Data.result) => {
  let (choiceToRemove, setChoiceToRemove) = React.useState(_ => None);
  let (responseToRemove, setResponseToRemove) = React.useState(_ => None);

  let removeChoice = (manageToken, choice) => {
    Js.Promise.(
      Api.removeChoice(manageToken, choice)
      |> then_(resultVariant => {
           switch (resultVariant) {
           | Data.ResultRes(_res) =>
             ReasonReactRouter.push("/manage-poll/" ++ manageToken);
             notify("info", "Results recalculated without choice");
             resolve();
           | Data.ResultErrors(_error) =>
             notify("error", "There was an issue removing the choice");
             resolve();
           }
         })
    )
    |> ignore;
  };

  let removeResponse = (manageToken, id) => {
    Js.Promise.(
      Api.destroyResponse(manageToken, id)
      |> then_((res: Fetch.Response.t) => {
           switch (Fetch.Response.status(res)) {
           | 200
           | 201
           | 204 =>
             ReasonReactRouter.push("/manage-poll/" ++ manageToken);
             notify("info", "Results recalculated without response");
             resolve();
           | _ =>
             notify("error", "There was an error removing this response");
             resolve();
           }
         })
    )
    |> ignore;
  };

  let renderResponse = (response: Data.resultResponse) => {
    <div className="remove-choice" key={response.name}>
      <div>
        <button
          className="button button-sm"
          onClick={_ => setResponseToRemove(_state => Some(response))}>
          <i className="far fa-trash-alt" />
        </button>
      </div>
      <div> {R.s(response.name)} </div>
    </div>;
  };

  let renderChoice = choice => {
    <div className="remove-choice" key=choice>
      <div>
        <button
          className="button button-sm"
          onClick={_ => setChoiceToRemove(_state => Some(choice))}>
          <i className="far fa-trash-alt" />
        </button>
      </div>
      <div> {R.s(choice)} </div>
    </div>;
  };

  let renderChoiceRemove = (poll: Data.poll) => {
    switch (poll.id, poll.manageToken) {
    | (Some(_takeToken), Some(_manageToken)) =>
      let showRemove = List.length(poll.choices) > 2;
      if (showRemove) {
        <div>
          <h4 className="centered"> {R.s("Select a choice to remove:")} </h4>
          <div className="remove-choice-list">
            {poll.choices
             |> List.map(renderChoice)
             |> Array.of_list
             |> React.array}
          </div>
        </div>;
      } else {
        <div> {R.s("Cannot remove a choice when only two exist.")} </div>;
      };
    | _ => React.null
    };
  };

  let renderResponseRemove = (result: Data.result) => {
    let showRemove = List.length(result.responses) > 0;
    if (showRemove) {
      <div>
        <h4 className="centered"> {R.s("Select a response to remove:")} </h4>
        <div className="remove-choice-list">
          {result.responses
           |> List.map(renderResponse)
           |> Array.of_list
           |> React.array}
        </div>
      </div>;
    } else {
      React.null;
    };
  };

  let renderChoiceRemovalConfirmation = (poll: Data.poll, choice) => {
    switch (poll.manageToken) {
    | None => React.null
    | Some(token) =>
      <div>
        <h4 className="centered"> {R.s("Are you sure?")} </h4>
        <p>
          {R.s(
             "'"
             ++ choice
             ++ "' will be permanently removed and the results will be recalculated",
           )}
        </p>
        <div className="centered">
          <button
            className="button m-h-sm"
            onClick={_ => setChoiceToRemove(_state => None)}>
            {R.s("Keep Choice")}
          </button>
          <button
            className="button m-h-sm"
            onClick={_ => removeChoice(token, choice)}>
            {R.s("Remove Choice")}
          </button>
        </div>
      </div>
    };
  };

  let renderResponseRemovalConfitmation =
      (poll: Data.poll, response: Data.resultResponse) => {
    switch (poll.manageToken) {
    | None => React.null
    | Some(token) =>
      <div>
        <h4 className="centered"> {R.s("Are you sure?")} </h4>
        <p>
          {R.s(
             "'"
             ++ response.name
             ++ "' will be permanently removed and the results will be recalculated",
           )}
        </p>
        <div className="centered">
          <button
            className="button m-h-sm"
            onClick={_ => setResponseToRemove(_state => None)}>
            {R.s("Keep Response")}
          </button>
          <button
            className="button m-h-sm"
            onClick={_ => removeResponse(token, response.id)}>
            {R.s("Remove Response")}
          </button>
        </div>
      </div>
    };
  };

  <div className="page">
    <h3 className="centered"> {R.s("Edit Results")} </h3>
    {switch (choiceToRemove, responseToRemove) {
     | (Some(choice), _) =>
       renderChoiceRemovalConfirmation(result.poll, choice)
     | (_, Some(response)) =>
       renderResponseRemovalConfitmation(result.poll, response)
     | _ =>
       <div>
         {renderChoiceRemove(result.poll)}
         {renderResponseRemove(result)}
         {switch (result.poll.manageToken) {
          | None => React.null
          | Some(manageToken) =>
            <div className="centered m-t-md">
              <button
                className="button"
                onClick={_ =>
                  ReasonReactRouter.push("/manage-poll/" ++ manageToken)
                }>
                {R.s("Back")}
              </button>
            </div>
          }}
       </div>
     }}
  </div>;
};