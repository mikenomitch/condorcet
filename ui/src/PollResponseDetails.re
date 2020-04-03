[@react.component]
let make = (~result: Data.result) => {
  let renderResponseCount = count => {
    switch (count) {
    | 0 => <p> {R.s("No responses yet")} </p>
    | 1 => <p> {R.s("1 response from: ")} </p>
    | count => <p> {R.s(string_of_int(count) ++ " responses:")} </p>
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
    | Some(comment) =>
      <p key={r.id}> <span> {(r.name ++ ": ")->R.s} </span> comment->R.s </p>
    | None => React.null
    };
  };

  let renderResponseComments = (responses: list(Data.resultResponse)) => {
    let with_comment =
      responses
      |> List.filter((r: Data.resultResponse) => {
           switch (r.comment) {
           | Some(_comment) => true
           | None => false
           }
         });

    switch (with_comment) {
    | [] => React.null
    | list =>
      <div>
        <br />
        <p> {R.s("Comments:")} </p>
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