[@react.component]
let make = (~placeholder, ~value, ~onChange, ~focusOnRender=false, ~label=?) => {
  let inputRef = React.useRef(None);

  React.useEffect0(() => {
    if (focusOnRender) {
      let current = React.Ref.current(inputRef);
      switch (current) {
      | Some(element) =>
        let node = ReactDOMRe.domElementToObj(element);
        ignore(node##focus());

      | None => ignore()
      };
    };
    None;
  });

  let input =
    <input
      ref={ReactDOMRe.Ref.callbackDomRef(elem =>
        React.Ref.setCurrent(inputRef, Js.Nullable.toOption(elem))
      )}
      className="input input-full-width"
      onChange
      value
      placeholder
    />;

  switch (label) {
  | None => input
  | Some(l) =>
    <div>
      <label> {R.s(l)} </label>
      <div className="m-t-sm"> input </div>
    </div>
  };
};