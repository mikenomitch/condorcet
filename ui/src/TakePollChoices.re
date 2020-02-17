type item = int;

module Item = {
  type t = item;
  let eq = (x1, x2) => x1 == x2;
};

module Container =
  Dnd.MakeSingletonContainer({});

module Items = Dnd.Make(Item, Container);

type state = array(item);

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

let initialState = [|1, 2, 3, 4, 5, 6, 7|];

[@react.component]
let make = () => {
  let (state, dispatch) = reducer->React.useReducer(initialState);
  let state_as_list = Array.to_list(state);

  <Items.DndManager onReorder={result => ReorderItems(result)->dispatch}>
    <Items.DroppableContainer id={Container.id()} axis=Y>
      {List.mapi(
         (index, item) => {
           <Items.DraggableItem
             id=item
             key={item->string_of_int}
             containerId={Container.id()}
             index>
             {`Children(item->string_of_int->React.string)}
           </Items.DraggableItem>
         },
         state_as_list,
       )
       ->Array.of_list
       ->React.array}
    </Items.DroppableContainer>
  </Items.DndManager>;
};