[@react.component]
let make = (~children) => {
  <div>
    <div onClick={_ => ReasonReactRouter.push("/")} className="header">
      {R.s("Poller.io")}
    </div>
    <div className="content"> children </div>
  </div>;
};