[@react.component]
let make = (~notify, ~result: Data.result) => {
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

  let renderChoice = (manageToken, choice) => {
    <div className="remove-choice" key=choice>
      <div>
        <button
          className="button button-sm"
          onClick={_ => removeChoice(manageToken, choice)}>
          <i className="far fa-trash-alt" />
        </button>
      </div>
      <div> {R.s(choice)} </div>
    </div>;
  };

  switch (result.poll.id, result.poll.manageToken, result.poll.id) {
  | (Some(_pollId), Some(manageToken), Some(_takeToken)) =>
    <div className="page">
      <h3 className="centered"> {R.s("Edit Choices")} </h3>
      <h4 className="centered"> {R.s("Select a choice to remove:")} </h4>
      <div className="remove-choice-list">
        {result.poll.choices
         |> List.map(renderChoice(manageToken))
         |> Array.of_list
         |> React.array}
      </div>
    </div>
  | _ => React.null
  };
};