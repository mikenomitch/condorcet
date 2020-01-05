[@react.component]
let make = (~id) => {
  let (result, setResult) = React.useState(() => None);

  React.useEffect0(() => {
    Api.fetchResult(id, setResult);
    None;
  });

  switch (result) {
  | None => <p> {React.string("None")} </p>
  | Some(result) =>
    <div className="page">
      <h3> {R.s("Results")} </h3>
      <PollResults result />
    </div>
  };
};