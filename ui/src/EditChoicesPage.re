[@react.component]
let make = (~manageToken, ~notify) => {
  let (result, setResult) = React.useState(() => None);

  React.useEffect0(() => {
    Api.fetchManageResult(manageToken, setResult);
    None;
  });

  switch (result) {
  | None => React.null
  | Some(result) => <EditChoices result notify />
  };
};