[@react.component]
let make = (~poll: Data.poll) => {
  let (choiceOrder, changeOrdering) = React.useState(() => poll.choices);
  let (name, changeName) = React.useState(_ => "");

  let move = (amount, idx) => {
    let newChoices = choiceOrder |> Array.of_list;
    let moving = newChoices[idx];
    let replacing = newChoices[idx + amount];
    newChoices[idx] = replacing;
    newChoices[idx + amount] = moving;
    let newList = Array.to_list(newChoices);
    changeOrdering(_ => newList);
  };

  let response: Data.response = {id: None, name, order: choiceOrder};

  let submitChoices = _ => {
    (
      switch (poll.id) {
      | None => Js.Promise.(resolve())
      | Some(id) =>
        Js.Promise.(
          Api.submitPoll(id, response)
          |> then_(_ => ReasonReactRouter.push("/results/" ++ id) |> resolve)
        )
      }
    )
    |> ignore;
  };

  let renderChoice = (idx, choice) => {
    let moveChoiceUp = _ => move(-1, idx);
    let moveChoiceDown = _ => move(1, idx);

    <div className="take-choice" key=choice>
      <p className="take-choice-text">
        {R.s(string_of_int(idx + 1))}
        {R.s(" - ")}
        {R.s(choice)}
      </p>
      {switch (idx) {
       | 0 => React.null
       | _ =>
         <div className="take-choice-btn">
           <button className="button button-sm" onClick=moveChoiceUp>
             {R.s({j|▲|j})}
           </button>
         </div>
       }}
      {idx + 1 == List.length(choiceOrder)
         ? React.null
         : <div className="take-choice-btn">
             <button
               className="button button-sm"
               disabled={idx + 1 == List.length(choiceOrder)}
               onClick=moveChoiceDown>
               {R.s({j|▼|j})}
             </button>
           </div>}
    </div>;
  };

  <div className="page">
    <h3> {R.s(poll.question)} </h3>
    <div className="take-poll-choice-list">
      {choiceOrder |> List.mapi(renderChoice) |> Array.of_list |> React.array}
    </div>
    <br />
    <br />
    <Input
      label="Your Name:"
      onChange={event => changeName(ReactEvent.Form.target(event)##value)}
      value=name
      placeholder="..."
    />
    <br />
    <br />
    <div className="centered">
      <button className="button button-mdlg" onClick=submitChoices>
        {R.s("Submit")}
      </button>
    </div>
  </div>;
};