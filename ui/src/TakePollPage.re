[@react.component]
let make = (~id) => {
  let (poll, setPoll) = React.useState(() => None);

  React.useEffect0(() => {
    Api.fetchPoll(id, setPoll) |> ignore;
    None;
  });

  switch (poll) {
  | None => <p> {React.string("None")} </p>
  | Some(poll) => <TakePoll poll />
  };
};