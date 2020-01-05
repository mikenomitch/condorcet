[@react.component]
let make = (~result: Data.result) => {
  <div className="page">
    <h3 className="centered"> {R.s("Poll: " ++ result.poll.question)} </h3>
    {switch (result.poll.id) {
     | Some(id) =>
       <div className="centered">
         <button
           className="button"
           onClick={_ => ReasonReactRouter.push("/take-poll/" ++ id)}>
           {R.s("Take the Poll Yourself")}
         </button>
       </div>
     | _ => React.null
     }}
    <div>
      <h3> {R.s("Links:")} </h3>
      {switch (result.poll.manageToken) {
       | Some(manageToken) =>
         <div className="link-holder">
           <p> {R.s("Manage Poll Link:")} </p>
           <CopyableLink link={"localhost:4000/manage-poll/" ++ manageToken} />
           <p> <b> {R.s("This link is a password. Don't lose it!")} </b> </p>
         </div>
       | None => React.null
       }}
      {switch (result.poll.id) {
       | Some(takeToken) =>
         <div className="link-holder">
           <p> {R.s("Take Poll Link:")} </p>
           <CopyableLink link={"localhost:4000/take-poll/" ++ takeToken} />
         </div>
       | None => React.null
       }}
    </div>
    <div> <h3> {R.s("Results:")} </h3> <PollResults result /> </div>
  </div>;
};