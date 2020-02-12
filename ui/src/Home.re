[@react.component]
let make = () => {
  <div className="page">
    <h3 className="centered"> {R.s("Make Better Group Decisions")} </h3>
    <p>
      {R.s(
         "Use Poller to make ranked polls with alternative election schemes.",
       )}
    </p>
    <p>
      {R.s(
         "Get results for Instant Runoff, Borda Count, and Simple Plurality elections.",
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
  </div>;
};