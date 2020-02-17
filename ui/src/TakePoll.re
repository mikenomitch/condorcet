module Item = {
  type t = string;
  let eq = (x1, x2) => x1 == x2;
};

module Container =
  Dnd.MakeSingletonContainer({});

module Items = Dnd.Make(Item, Container);

type state = array(string);

type action =
  | ReorderItems(Dnd.result(Item.t, Container.t));

let reducer = (state, action) =>
  switch (action) {
  | ReorderItems(Some(SameContainer(item, placement))) =>
    state->ArrayExt.reinsert(
      ~value=item,
      ~place=
        switch (placement) {
        | Before(id) => `Before(id)
        | Last => `Last
        },
    )
  | ReorderItems(Some(NewContainer(_)))
  | ReorderItems(None) => state
  };

[@react.component]
let make = (~poll: Data.poll) => {
  let (name, changeName) = React.useState(_ => "");
  let (state, dispatch) =
    reducer->React.useReducer(Array.of_list(poll.choices));
  let state_as_list = Array.to_list(state);
  let response: Data.response = {id: None, name, order: state_as_list};

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

  let renderIt = (index: int, choice: string) => {
    <div className="take-choice" key=choice>

        <p className="take-choice-text">
          {R.s(string_of_int(index + 1))}
          {R.s(" - ")}
          {R.s(choice)}
        </p>
      </div>;
      // {switch (index) {
      //  | 0 => React.null
      //  | _ =>
      //    <div className="take-choice-btn">
      //      <button className="button button-sm"> {R.s({j|▲|j})} </button>
      //    </div>
      //  }}
      // {index + 1 == Array.length(state)
      //    ? React.null
      //    : <div className="take-choice-btn">
      //        <button
      //          className="button button-sm"
      //          disabled={index + 1 == Array.length(state)}>
      //          {R.s({j|▼|j})}
      //        </button>
      //      </div>}
  };

  let renderChoice = (index, choice) => {
    <Items.DraggableItem
      id=choice key=choice containerId={Container.id()} index>
      {`Children(renderIt(index, choice))}
    </Items.DraggableItem>;
  };

  <div className="page">
    <h3> {R.s(poll.question)} </h3>
    <div className="take-poll-choice-list">
      <Items.DndManager onReorder={result => ReorderItems(result)->dispatch}>
        <Items.DroppableContainer id={Container.id()} axis=Y>
          {state
           |> Array.to_list
           |> List.mapi(renderChoice)
           |> Array.of_list
           |> React.array}
        </Items.DroppableContainer>
      </Items.DndManager>
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