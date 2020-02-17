module Item = {
  type t = string;
  let eq = (x1, x2) => x1 == x2;
};

module Container =
  Dnd.MakeSingletonContainer({});

module Items = Dnd.Make(Item, Container);

let move = (choices, idx, amount) => {
  let newChoices = choices->Array.to_list->Array.of_list;
  let moving = newChoices[idx];
  let replacing = newChoices[idx + amount];
  newChoices[idx] = replacing;
  newChoices[idx + amount] = moving;
  newChoices;
};

type state = array(string);

type action =
  | ReorderItems(Dnd.result(Item.t, Container.t))
  | MoveUp(int)
  | MoveDown(int);

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
  | MoveUp(idx) => move(state, idx, -1)
  | MoveDown(idx) => move(state, idx, 1)
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
    <div className="take-choice-inner">
      <p className="take-choice-text">
        {R.s(string_of_int(index + 1))}
        {R.s(" - ")}
        {R.s(choice)}
      </p>
      {switch (index) {
       | 0 => React.null
       | _ =>
         <div className="take-choice-btn">
           <button
             onClick={_any => dispatch(MoveUp(index))}
             className="button button-sm">
             {R.s({j|▲|j})}
           </button>
         </div>
       }}
      {index + 1 == Array.length(state)
         ? React.null
         : <div className="take-choice-btn">
             <button
               className="button button-sm"
               onClick={_any => dispatch(MoveDown(index))}
               disabled={index + 1 == Array.length(state)}>
               {R.s({j|▼|j})}
             </button>
           </div>}
    </div>;
  };

  let renderChoice = (index, choice) => {
    <Items.DraggableItem
      className={(~dragging: bool) => "take-choice"}
      id=choice
      key=choice
      containerId={Container.id()}
      index>
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