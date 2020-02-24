[@react.component]
let make = (~placeholder, ~value, ~onChange, ~label=?) => {
  let input =
    <input className="input input-full-width" onChange value placeholder />;

  switch (label) {
  | None => input
  | Some(l) =>
    <div>
      <label> {R.s(l)} </label>
      <div className="m-t-sm"> input </div>
    </div>
  };
};