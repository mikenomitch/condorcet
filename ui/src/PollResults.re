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
           ? "The ranked choice winners are: "
           : "The ranked choice winner is: ";

       let bordaString =
         List.length(winnerMap.borda) > 1
           ? "The borda count winners are: " : "The borda count winner is: ";

       let pluralityString =
         List.length(winnerMap.plurality) > 1
           ? "The plurality winners are: " : "The plurality winner is: ";

       <div>
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