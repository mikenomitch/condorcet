[@react.component]
let make = (~result: Data.result) => {
  let renderResponseCount = count => {
    switch (count) {
    | 0 => <p> {R.s("No responses yet")} </p>
    | 1 => <p> {R.s("1 response from: ")} </p>
    | count => <p> {R.s(string_of_int(count) ++ " responses from:")} </p>
    };
  };

  let renderResponseNames = responses => {
    switch (List.map((r: Data.resultResponse) => r.name, responses)) {
    | [] => React.null
    | nameList =>
      <p> {nameList |> Array.of_list |> Js.Array.joinWith(", ") |> R.s} </p>
    };
  };

  <div className="responses-holder">
    {renderResponseCount(result.responseCount)}
    {renderResponseNames(result.responses)}
  </div>;
};