[@react.component]
let make = (~checked, ~onChange, ~label, ~name) => {
  <label className="checkbox">
    <input name type_="checkbox" checked onChange />
    {R.s(label)}
  </label>;
};