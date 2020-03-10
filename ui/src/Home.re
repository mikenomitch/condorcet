[@react.component]
let make = () => {
  <div className="page">
    <h3 className="centered"> {R.s("Make Better Group Decisions")} </h3>
    <p className="centered">
      {R.s("Use Poller to make group decisions using ranked voting.")}
    </p>
    <p className="centered">
      {R.s(
         "Get results for Instant Runoff Voting, Borda Counts, the Condorcet Method, and Plurality elections.",
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
      <Link className="centered" linkTo="/why">
        {R.s("What are the advantages compared to standard elections?")}
      </Link>
    </p>
  </div>;
};