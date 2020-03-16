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
    switch (responses) {
    | [] => React.null
    | list =>
      <p>
        {list
         |> List.map((r: Data.resultResponse) => r.name)
         |> Array.of_list
         |> Js.Array.joinWith(", ")
         |> R.s}
      </p>
    };
  };

  let renderComment = (r: Data.resultResponse) => {
    switch (r.comment) {
    | Some(comment) => <p> <b> {(r.name ++ ":")->R.s} </b> comment->R.s </p>
    | None => React.null
    };
  };

  let renderResponseComments = (responses: list(Data.resultResponse)) => {
    switch (responses) {
    | [] => React.null
    | list =>
      <div>
        {List.map(renderComment, list) |> Array.of_list |> React.array}
      </div>
    };
  };

  <div className="responses-holder">
    {renderResponseCount(result.responseCount)}
    {renderResponseNames(result.responses)}
    {renderResponseComments(result.responses)}
  </div>;
};