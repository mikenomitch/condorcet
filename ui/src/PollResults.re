type nameAndRes = {
  key: string,
  res: int,
};

[@react.component]
let make = (~result: Data.result, ~showLink=false) => {
  let (showingFullResults, setFullResults) = React.useState(() => false);
  let changeFullRes = _ => setFullResults(_ => !showingFullResults);

  let renderWinners = winnersList => {
    <b> {R.s(winnersList |> Array.of_list |> Js.Array.joinWith(", "))} </b>;
  };

  let renderRankedResults = rankedResults => {
    <div>
      {rankedResults
       |> List.mapi((idx, winners) => {
            <div key={idx->string_of_int}>
              <i className="fw-normal">
                <Ordinal num={idx + 1} />
                {R.s(": ")}
              </i>
              {winners |> Array.of_list |> Js.Array.joinWith(", ") |> R.s}
            </div>
          })
       |> Array.of_list
       |> React.array}
    </div>;
  };

  let renderFullBorda = (resultMap, unit, units) => {
    <div>
      {Js.Dict.keys(resultMap)
       |> Array.to_list
       |> List.map(key => {
            switch (Js.Dict.get(resultMap, key)) {
            | Some(res) => {key, res}
            | _ => {key, res: 0}
            }
          })
       |> List.sort((a, b) => {
            switch (a.res < b.res, a.res == b.res) {
            | (true, _) => 1
            | (_, true) => 0
            | _ => (-1)
            }
          })
       |> List.map(({key, res}) => {
            <div key className="full-results">
              <i className="fw-normal"> {R.s(key ++ ": ")} </i>
              {switch (res) {
               | 1 => R.s(res->string_of_int ++ " " ++ unit)
               | _ => R.s(res->string_of_int ++ " " ++ units)
               }}
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
              <i className="fw-normal"> {R.s(key ++ ": ")} </i>
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

  let renderResultsLink = () => {
    switch (result.poll.id) {
    | Some(id) =>
      <div className="resuts-link-holder">
        <p> <b> {R.s("Save this URL to return to results:")} </b> </p>
        <CopyableLink link={Constants.host ++ "/results/" ++ id} />
      </div>
    | _ => React.null
    };
  };

  result.responseCount == 0
    ? <h4> {R.s("No responses yet")} </h4>
    : <div>
        <div className="results-title">
          <h3> {R.s("Results")} </h3>
          {switch (result.winners) {
           | Some(_winners) =>
             <button className="button button-sm" onClick=changeFullRes>
               {R.s(
                  showingFullResults
                    ? "Hide full results" : "Show full results",
                )}
             </button>
           | _ => React.null
           }}
        </div>
        {switch (result.winners, result.fullResults) {
         | (Some(winnerMap), Some(resultsMap)) =>
           let rankedString =
             renderWinnerString(winnerMap.ranked, "Instant Runoff");
           let bordaString =
             renderWinnerString(winnerMap.borda, "Borda Count");
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
             {showingFullResults
                ? renderRankedResults(resultsMap.ranked) : React.null}
             <p> {R.s(bordaString)} {renderWinners(winnerMap.borda)} </p>
             {showingFullResults
                ? renderFullBorda(resultsMap.borda, "point", "points")
                : React.null}
             <p>
               {R.s(pluralityString)}
               {renderWinners(winnerMap.plurality)}
             </p>
             {showingFullResults
                ? renderFullResult(
                    resultsMap.plurality,
                    "first place vote",
                    "first place votes",
                  )
                : React.null}
             {switch (result.winners) {
              | Some(_winners) =>
                <div className="m-t-sm">
                  <a href="/why#alternative-methods">
                    {R.s("What do these results mean?")}
                  </a>
                </div>
              | _ => React.null
              }}
           </div>;
         | _ => React.null
         }}
        <PollResponseDetails result />
        {showLink ? renderResultsLink() : React.null}
      </div>;
};