[@react.component]
let make = (~notify, ~result: Data.result) => {
  let (choiceToRemove, setChoiceToRemove) = React.useState(_ => None);
  let (ballotToRemove, setBallotToRemove) = React.useState(_ => None);

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

  let removeBallot = (_manageToken, name) => {
    notify("info", "TODO: " ++ name);
  };

  let renderResponse = name => {
    <div className="remove-choice" key=name>
      <div>
        <button
          className="button button-sm"
          onClick={_ => setBallotToRemove(_state => Some(name))}>
          <i className="far fa-trash-alt" />
        </button>
      </div>
      <div> {R.s(name)} </div>
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

  let renderBallotRemove = (result: Data.result) => {
    <div>
      <h4 className="centered"> {R.s("Select a response to remove:")} </h4>
      <div className="remove-choice-list">
        {result.names
         |> List.map(renderResponse)
         |> Array.of_list
         |> React.array}
      </div>
    </div>;
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

  let renderBallotRemoveConfirmation = (poll: Data.poll, name) => {
    switch (poll.manageToken) {
    | None => React.null
    | Some(token) =>
      <div>
        <h4 className="centered"> {R.s("Are you sure?")} </h4>
        <p>
          {R.s(
             "'"
             ++ name
             ++ "' will be permanently removed and the results will be recalculated",
           )}
        </p>
        <div className="centered">
          <button
            className="button m-h-sm"
            onClick={_ => setBallotToRemove(_state => None)}>
            {R.s("Keep Response")}
          </button>
          <button
            className="button m-h-sm"
            onClick={_ => removeBallot(token, name)}>
            {R.s("Remove Response")}
          </button>
        </div>
      </div>
    };
  };

  <div className="page">
    <h3 className="centered"> {R.s("Edit Results")} </h3>
    {switch (choiceToRemove, ballotToRemove) {
     | (Some(choice), _) =>
       renderChoiceRemovalConfirmation(result.poll, choice)
     | (_, Some(ballot)) =>
       renderBallotRemoveConfirmation(result.poll, ballot)
     | _ =>
       <div>
         {renderChoiceRemove(result.poll)}
         {renderBallotRemove(result)}
       </div>
     }}
  </div>;
};