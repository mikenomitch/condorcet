[@react.component]
let make = (~result: Data.result) => {
  <div>
    <h1> {R.s("Poll: " ++ result.poll.question)} </h1>
    {switch (result.poll.id) {
     | Some(id) =>
       <button
         onClick={_ =>
           ReasonReactRouter.push("/take-poll/" ++ string_of_int(id))
         }>
         {R.s("Take the Poll Yourself")}
       </button>
     | _ => React.null
     }}
    <div>
      <h2> {R.s("Links")} </h2>
      <p> {R.s("Link to take poll: http://zombo.com/poll/12345")} </p>
      <p>
        {R.s(
           "Save this link to manage the poll in the future: http://zombo.com/poll/12345/manage/token",
         )}
      </p>
    </div>
    <PollResults result />
  </div>;
};