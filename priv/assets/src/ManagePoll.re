[@react.component]
let make = (~result: Data.result) => {
  <div>
    <h1> {R.s("Poll: " ++ result.poll.question)} </h1>
    {switch (result.poll.id) {
     | Some(id) =>
       <button onClick={_ => ReasonReactRouter.push("/take-poll/" ++ id)}>
         {R.s("Take the Poll Yourself")}
       </button>
     | _ => React.null
     }}
    <div>
      <h2> {R.s("Links")} </h2>
      {switch (result.poll.id) {
       | Some(takeToken) =>
         <p>
           {R.s("Link to take poll: localhost:1234/take-poll/" ++ takeToken)}
         </p>
       | None => React.null
       }}
      {switch (result.poll.manageToken) {
       | Some(manageToken) =>
         <p>
           {R.s("Link to take poll: localhost:1234/take-poll/" ++ manageToken)}
         </p>
       | None => React.null
       }}
    </div>
    <PollResults result />
  </div>;
};