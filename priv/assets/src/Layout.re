[@react.component]
let make = (~children) => {
  <div>
    <div onClick={_ => ReasonReactRouter.push("/")} style=Style.header>
      {R.s("Condorcet")}
    </div>
    children
  </div>;
};