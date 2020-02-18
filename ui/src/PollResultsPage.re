[@react.component]
let make = (~id) => {
  let (result, setResult) = React.useState(() => None);

  React.useEffect0(() => {
    Api.fetchResult(id, setResult);
    None;
  });

  switch (result) {
  | None => React.null
  | Some(result) => <div className="page"> <PollResults result /> </div>
  };
};