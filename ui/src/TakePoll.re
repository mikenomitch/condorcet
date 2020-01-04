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
          |> then_(_ =>
               ReasonReactRouter.push("/results/" ++ id)
               |> resolve
             )
        )
      }
    )
    |> ignore;
  };

  let renderChoice = (idx, choice) => {
    let moveChoiceUp = _ => move(-1, idx);
    let moveChoiceDown = _ => move(1, idx);

    <div key={string_of_int(idx)}>
      <p> {R.s(choice)} </p>
      <button disabled={idx == 0} onClick=moveChoiceUp> {R.s("Up")} </button>
      <button
        disabled={idx + 1 == List.length(choiceOrder)} onClick=moveChoiceDown>
        {R.s("Down")}
      </button>
    </div>;
  };

  <div>
    <h1> {R.s(poll.question)} </h1>
    <div>
      {choiceOrder |> List.mapi(renderChoice) |> Array.of_list |> React.array}
    </div>
    <br />
    <br />
    <input
      onChange={event => changeName(ReactEvent.Form.target(event)##value)}
      value=name
      placeholder="Your Name..."
    />
    <br />
    <br />
    <button onClick=submitChoices> {R.s("Submit")} </button>
  </div>;
};