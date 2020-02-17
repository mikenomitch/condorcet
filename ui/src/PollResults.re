[@react.component]
let make = (~result: Data.result) => {
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
      <p> {R.s(nameList |> Array.of_list |> Js.Array.joinWith(", "))} </p>
    };
  };

  <div>
    {switch (result.winners) {
     | Some(winnerMap) =>
       let rankedString =
         List.length(winnerMap.ranked) > 1
           ? "Ranked choice winners: " : "Ranked choice winner: ";

       let bordaString =
         List.length(winnerMap.borda) > 1
           ? "Borda count winners: " : "Borda count winner: ";

       let pluralityString =
         List.length(winnerMap.plurality) > 1
           ? "Plurality winners: " : "Plurality winner: ";

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
         <p> {R.s(bordaString)} {renderWinners(winnerMap.borda)} </p>
         <p> {R.s(pluralityString)} {renderWinners(winnerMap.plurality)} </p>
       </div>;
     | None => React.null
     }}
    <div className="responses-holder">
      {renderResponseCount(result.responseCount)}
      {renderResponseNames(result.names)}
    </div>
  </div>;
};