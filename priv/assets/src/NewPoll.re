[@react.component]
let make = () => {
  let blankPoll: Data.poll = {
    id: Some(1),
    question: "",
    choices: ["", "", "", ""],
  };
  let (poll, setPoll) = React.useState(() => blankPoll);

  let changeQuestion = question => {
    setPoll(_ => {...poll, question});
  };

  let changeChoice = (newChoice, idx) => {
    let newChoices = poll.choices |> Array.of_list;
    newChoices[idx] = newChoice;
    let newList = Array.to_list(newChoices);
    setPoll(_ => {...poll, choices: newList});
  };

  let addChoice = _ => {
    setPoll(_ => {...poll, choices: List.append(poll.choices, [""])});
  };

  let savePoll = _ => {
    Js.Promise.(
      Api.createPoll(poll)
      |> then_(json => Data.Decode.dPoll(json) |> resolve)
      |> then_((poll: Data.poll) =>
           switch (poll.id) {
           | Some(id) =>
             ReasonReactRouter.push("/manage-poll/" ++ string_of_int(id))
             |> resolve
           | _ => ReasonReactRouter.push("/manage-poll/1") |> resolve
           }
         )
    )
    |> ignore;
  };

  let renderChoice = (idx, answer) => {
    <div key={string_of_int(idx)}>
      <input
        onChange={event =>
          changeChoice(ReactEvent.Form.target(event)##value, idx)
        }
        value=answer
        placeholder="Choice..."
      />
    </div>;
  };

  <div>
    <h2> {R.s("Make a Poll")} </h2>
    <div>
      <input
        onChange={event =>
          changeQuestion(ReactEvent.Form.target(event)##value)
        }
        value={poll.question}
        placeholder="Question..."
      />
    </div>
    <br />
    <br />
    <div>
      {poll.choices |> List.mapi(renderChoice) |> Array.of_list |> React.array}
    </div>
    <br />
    <br />
    <div> <button onClick=addChoice> {R.s("+")} </button> </div>
    <br />
    <br />
    <div> <button onClick=savePoll> {R.s("Save")} </button> </div>
  </div>;
};