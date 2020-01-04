[@react.component]
let make = (~manageToken) => {
  let (result, setResult) = React.useState(() => None);

  React.useEffect0(() => {
    Api.fetchManageResult(manageToken, setResult);
    None;
  });

  switch (result) {
  | None => <p> {React.string("None")} </p>
  | Some(result) => <ManagePoll result />
  };
};