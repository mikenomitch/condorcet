[@bs.val] external alert: string => unit = "alert";

module RList = Rationale.RList;

[@react.component]
let make = (~notify) => {
  let blankPoll: Data.poll = {
    id: None,
    question: "",
    choices: ["", "", "", ""],
    manageToken: None,
  };
  let (poll, setPoll) = React.useState(() => blankPoll);
  let (hasAdded, setHasAdded) = React.useState(() => false);
  let showButtons = poll.choices |> List.length > 2;

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
    setHasAdded(_ => true);
    setPoll(_ => {...poll, choices: List.append(poll.choices, [""])});
  };

  let removeChoice = idx => {
    let newChoices = RList.remove(idx, 1, poll.choices);
    setPoll(_ => {...poll, choices: newChoices});
  };

  let savePoll = _ => {
    Js.Promise.(
      Api.createPoll(poll, notify)
      |> then_(res => {
           switch (res) {
           | None => resolve()
           | Some((poll: Data.poll)) =>
             switch (poll.manageToken) {
             | Some(manageToken) =>
               ReasonReactRouter.push("/manage-poll/" ++ manageToken)
               |> resolve
             | _ =>
               notify("error", "There was an issue making this poll");
               resolve();
             }
           }
         })
    )
    |> ignore;
  };

  let renderChoice = (idx, answer) => {
    let finalChoice = idx + 1 == List.length(poll.choices);
    <div className="choice" key={string_of_int(idx)}>
      <Input
        focusOnRender={finalChoice && hasAdded}
        onChange={event =>
          changeChoice(ReactEvent.Form.target(event)##value, idx)
        }
        value=answer
        placeholder="Choice..."
      />
      {showButtons
         ? <div>
             <button
               className="button button-sm" onClick={_ => removeChoice(idx)}>
               <i className="far fa-trash-alt" />
             </button>
           </div>
         : React.null}
    </div>;
  };

  <div className="page">
    <h3 className="centered"> {R.s("Create a Poll")} </h3>
    <div className="poll-form">
      <div>
        <Input
          focusOnRender=true
          label="Your Question:"
          onChange={event =>
            changeQuestion(ReactEvent.Form.target(event)##value)
          }
          value={poll.question}
          placeholder="Question..."
        />
      </div>
      <div className="choice-list">
        <label className="input-label"> {R.s("Options:")} </label>
        {poll.choices
         |> List.mapi(renderChoice)
         |> Array.of_list
         |> React.array}
      </div>
      <div className="new-choice-holder">
        <button className="button" onClick=addChoice>
          <i className="fas fa-plus" />
          {R.s(" Add Choice")}
        </button>
      </div>
    </div>
    <div className="centered save-holder">
      <button className="button button-mdlg" onClick=savePoll>
        {R.s("Create Poll")}
      </button>
    </div>
  </div>;
};