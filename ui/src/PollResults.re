[@react.component]
let make = (~result: Data.result) => {
  let (showingFullResults, setFullResults) = React.useState(() => false);
  let changeFullRes = _ => setFullResults(_ => !showingFullResults);

  let renderWinners = winnersList => {
    <b> {R.s(winnersList |> Array.of_list |> Js.Array.joinWith(", "))} </b>;
  };

  let renderResponseCount = count => {
    switch (count) {
    | 0 => <p> {R.s("No responses yet")} </p>
    | 1 => <p> {R.s("1 response from: ")} </p>
    | count => <p> {R.s(string_of_int(count) ++ " responses from:")} </p>
    };
  };

  let renderResponseNames = names => {
    switch (names) {
    | [] => React.null
    | nameList =>
      <p> {nameList |> Array.of_list |> Js.Array.joinWith(", ") |> R.s} </p>
    };
  };

  let renderRankedResults = rankedResults => {
    <div>
      {rankedResults
       |> List.mapi((idx, winners) => {
            <div>
              <i> <Ordinal num={idx + 1} /> {R.s(": ")} </i>
              {winners |> Array.of_list |> Js.Array.joinWith(", ") |> R.s}
            </div>
          })
       |> Array.of_list
       |> React.array}
    </div>;
  };

  let renderFullResult = (resultMap, unit, units) => {
    <div>
      {Js.Dict.keys(resultMap)
       |> Array.to_list
       |> List.map(key => {
            <div key className="full-results">
              <i> {R.s(key ++ ": ")} </i>
              {switch (Js.Dict.get(resultMap, key)) {
               | Some(res) =>
                 switch (res) {
                 | 1 => R.s(res->string_of_int ++ " " ++ unit)
                 | _ => R.s(res->string_of_int ++ " " ++ units)
                 }
               | None => React.null
               }}
            </div>
          })
       |> Array.of_list
       |> React.array}
    </div>;
  };

  let renderWinnerString = (lst, typ) => {
    typ ++ (List.length(lst) > 1 ? " winners: " : " winner: ");
  };

  <div>
    <div className="results-title">
      <h3> {R.s("Results")} </h3>
      <button className="button button-sm" onClick=changeFullRes>
        {R.s(showingFullResults ? "Hide full results" : "Show full results")}
      </button>
    </div>
    {switch (result.winners, result.fullResults) {
     | (Some(winnerMap), Some(resultsMap)) =>
       let rankedString =
         renderWinnerString(winnerMap.ranked, "Ranked choice");
       let bordaString = renderWinnerString(winnerMap.borda, "Borda count");
       let pluralityString =
         renderWinnerString(winnerMap.plurality, "Plurality");

       <div>
         {switch (winnerMap.condorcet) {
          | Some(condorcetWinner) =>
            <p>
              {R.s("Condorcet Winner: ")}
              <b> {R.s(condorcetWinner)} </b>
            </p>
          | _ => <p> {R.s("No Condorcet Winner")} </p>
          }}
         <p> {R.s(rankedString)} {renderWinners(winnerMap.ranked)} </p>
         {if (showingFullResults) {
            renderRankedResults(resultsMap.ranked);
          } else {
            React.null;
          }}
         <p> {R.s(bordaString)} {renderWinners(winnerMap.borda)} </p>
         {if (showingFullResults) {
            renderFullResult(resultsMap.borda, "point", "points");
          } else {
            React.null;
          }}
         <p> {R.s(pluralityString)} {renderWinners(winnerMap.plurality)} </p>
         {if (showingFullResults) {
            renderFullResult(
              resultsMap.plurality,
              "first place vote",
              "first place votes",
            );
          } else {
            React.null;
          }}
       </div>;
     | _ => React.null
     }}
    <div className="responses-holder">
      {renderResponseCount(result.responseCount)}
      {renderResponseNames(result.names)}
    </div>
  </div>;
};