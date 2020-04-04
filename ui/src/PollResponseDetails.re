[@react.component]
let make = (~result: Data.result) => {
  let renderResponseCount = count => {
    switch (count) {
    | 0 => <h5> {R.s("No responses yet")} </h5>
    | 1 => <h5> {R.s("1 response from: ")} </h5>
    | count => <h5> {R.s(string_of_int(count) ++ " responses:")} </h5>
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
      <p key={r.id}>
        <span className="fw-normal"> {(r.name ++ ":  ")->R.s} </span>
        comment->R.s
      </p>
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
        <h5> {R.s("Comments:")} </h5>
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