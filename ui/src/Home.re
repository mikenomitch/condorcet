[@react.component]
let make = () => {
  <div className="page">
    <h3 className="centered"> {R.s("Make Better Group Decisions")} </h3>
    <p className="centered">
      {R.s(
         "Use Poller to make ranked decisions using multiple election methods.",
       )}
    </p>
    <p className="centered">
      {R.s(
         "Get results of instant runoffs, Borda Counts, the Condorcet method, and simple plurality elections.",
       )}
    </p>
    <br />
    <div className="centered">
      <button
        className="button button-mdlg"
        onClick={_ => ReasonReactRouter.push("/new")}>
        {R.s("Create a Poll")}
      </button>
    </div>
    <br />
    <p className="centered">
      <a className="centered" onClick={_ => ReasonReactRouter.push("/why")}>
        {R.s("What are the advantages compared to standard elections?")}
      </a>
    </p>
  </div>;
};