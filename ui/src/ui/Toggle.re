[@react.component]
let make = (~on, ~onClick, ~label=?) => {
  let btn =
    <button onClick className="button button-sm">
      <i className="fas fa-power-off" />
    </button>;

  switch (label) {
  | None => btn
  | Some(l) =>
    <div> <label> {R.s(l)} </label> <div className="m-t-sm"> btn </div> </div>
  };
};