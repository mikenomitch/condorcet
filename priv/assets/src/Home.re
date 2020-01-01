[@react.component]
let make = () => {
  <div>
    <h1> {R.s("Condorcet Home")} </h1>
    <button onClick={_ => ReasonReactRouter.push("/new")}>
      {R.s("Create a Poll")}
    </button>
  </div>;
};