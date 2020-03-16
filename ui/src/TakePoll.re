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
let make = (~poll: Data.poll, ~notify) => {
  let (name, changeName) = React.useState(_ => "");
  let (comment, changeComment) = React.useState(_ => None);

  let (state, dispatch) =
    reducer->React.useReducer(Array.of_list(poll.choices));
  let state_as_list = Array.to_list(state);
  let response: Data.response = {
    id: None,
    name,
    comment,
    order: state_as_list,
  };

  let submitChoices = _ => {
    (
      switch (poll.id) {
      | None => Js.Promise.(resolve())
      | Some(id) =>
        Js.Promise.(
          Api.submitPoll(id, response)
          |> then_(responseVariant => {
               switch (responseVariant) {
               | Data.ResponseErrors(_errors) =>
                 notify("error", "You must provide a name");
                 resolve();
               | Data.ResponseRes(_resp) =>
                 ReasonReactRouter.push("/results/" ++ id) |> resolve
               }
             })
        )
      }
    )
    |> ignore;
  };

  let renderChoiceChild = (index: int, choice: string) => {
    <div className="take-choice-draggable-inner">
      <p className="take-choice-text"> {R.s(choice)} </p>
      {switch (index) {
       | 0 => React.null
       | _ =>
         <div className="take-choice-btn">
           <button
             onClick={_any => dispatch(MoveUp(index))}
             className="button button-sm">
             <i className="fas fa-angle-up" />
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
               <i className="fas fa-angle-down" />
             </button>
           </div>}
    </div>;
  };

  let renderChoice = (index, choice) => {
    <div key={choice ++ string_of_int(index)} className="take-choice">
      <div className="take-choice-number">
        {R.s(string_of_int(index + 1) ++ ". ")}
      </div>
      <Items.DraggableItem
        className={(~dragging as _ignore) => "take-choice-draggable"}
        id=choice
        key={choice ++ string_of_int(index)}
        containerId={Container.id()}
        index>
        {`Children(renderChoiceChild(index, choice))}
      </Items.DraggableItem>
    </div>;
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
    <Input
      label="Comment:"
      onChange={event => {
        let comment = ReactEvent.Form.target(event)##value;
        changeComment(comment);
      }}
      value={
        switch (comment) {
        | Some(cmt) => cmt
        | None => ""
        }
      }
      placeholder="(optional)"
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