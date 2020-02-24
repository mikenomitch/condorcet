type notification = {
  t: string,
  text: string,
};

[@react.component]
let make = (~notifications: list(notification)) => {
  let renderNotification = (idx, n: notification) => {
    let className = "notification " ++ n.t;
    <div key={string_of_int(idx)} className> {R.s(n.text)} </div>;
  };

  <div className="notifications">
    {notifications
     |> List.mapi(renderNotification)
     |> Array.of_list
     |> React.array}
  </div>;
};