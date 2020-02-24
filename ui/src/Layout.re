[@react.component]
let make = (~notifications, ~children) => {
  <div>
    <Notifications notifications />
    <div onClick={_ => ReasonReactRouter.push("/")} className="header">
      {R.s("Poller.io")}
    </div>
    <div className="content"> children </div>
  </div>;
};