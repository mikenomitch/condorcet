[@react.component]
let make = (~id, ~addError) => {
  let (poll, setPoll) = React.useState(() => None);

  React.useEffect0(() => {
    Api.fetchPoll(id, setPoll) |> ignore;
    None;
  });

  switch (poll) {
  | None => React.null
  | Some(poll) => <TakePoll addError poll />
  };
};