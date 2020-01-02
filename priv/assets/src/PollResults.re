[@react.component]
let make = (~result: Data.result) => {
  <div>
    <h2> {R.s("Results")} </h2>
    {switch (result.winners) {
     | Some(winnerMap) =>
       <div>
         <p>
           {R.s("The ranked choice winner is:")}
           <b>
             {R.s(
                winnerMap.ranked |> Array.of_list |> Js.Array.joinWith(", "),
              )}
           </b>
         </p>
         <p>
           {R.s("The borda count winner is:")}
           <b>
             {R.s(
                winnerMap.borda |> Array.of_list |> Js.Array.joinWith(", "),
              )}
           </b>
         </p>
         <p>
           {R.s("The plurality winner is:")}
           <b>
             {R.s(
                winnerMap.plurality
                |> Array.of_list
                |> Js.Array.joinWith(", "),
              )}
           </b>
         </p>
       </div>
     | None => React.null
     }}
    <p> {R.s(string_of_int(result.responseCount) ++ " response(s)")} </p>
  </div>;
};