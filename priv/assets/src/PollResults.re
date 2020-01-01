[@react.component]
let make = (~result: Data.result) => {
  <div>
    <h2> {R.s("Results")} </h2>
    <p>
      {R.s("The condorcet winner is '")}
      <b> {R.s(result.winner)} </b>
      {R.s("'")}
    </p>
    <p> {R.s(string_of_int(result.responseCount) ++ " response(s)")} </p>
  </div>;
};