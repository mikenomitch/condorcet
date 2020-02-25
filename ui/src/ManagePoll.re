[@react.component]
let make = (~result: Data.result) => {
  let renderManage = (pollId, manageToken, takeToken) => {
    <div className="page">
      <h3 className="centered"> {R.s(result.poll.question)} </h3>
      <div className="centered">
        <button
          className="button"
          onClick={_ => ReasonReactRouter.push("/take-poll/" ++ pollId)}>
          {R.s("Take the Poll Yourself")}
        </button>
      </div>
      <div className="link-holder">
        <h4> {R.s("Manage Poll Link")} </h4>
        <CopyableLink
          link={Constants.host ++ "/manage-poll/" ++ manageToken}
        />
        <p> <b> {R.s("This link is a password. Don't lose it!")} </b> </p>
      </div>
      <div className="link-holder">
        <h4> {R.s("Take Poll Link")} </h4>
        <CopyableLink link={Constants.host ++ "/take-poll/" ++ takeToken} />
      </div>
      <PollResults result />
      <div>
        <button
          className="button"
          onClick={_ =>
            ReasonReactRouter.push(
              "/manage-poll/" ++ manageToken ++ "/edit-choices",
            )
          }>
          {R.s("Edit Choices")}
        </button>
      </div>
    </div>;
  };

  switch (result.poll.id, result.poll.manageToken, result.poll.id) {
  | (Some(pollId), Some(manageToken), Some(takeToken)) =>
    renderManage(pollId, manageToken, takeToken)
  | _ => React.null
  };
};