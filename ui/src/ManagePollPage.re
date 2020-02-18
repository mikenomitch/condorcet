[@react.component]
let make = (~manageToken) => {
  let (result, setResult) = React.useState(() => None);

  React.useEffect0(() => {
    Api.fetchManageResult(manageToken, setResult);
    None;
  });

  switch (result) {
  | None => React.null
  | Some(result) => <ManagePoll result />
  };
};