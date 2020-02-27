[@bs.val] external setTimeout: (unit => unit, int) => float = "setTimeout";

[@react.component]
let make = () => {
  let (notifications, setNotifications) = React.useState(() => []);
  let notify = (notificationType, text) => {
    let notif: Notifications.notification = {t: notificationType, text};
    setNotifications(_ => [notif]);
    setTimeout(() => {setNotifications(_state => [])}, 3000) |> ignore;
  };

  let url = ReasonReact.Router.useUrl();

  let body =
    switch (url.path) {
    | [] => <Home />
    | ["why"] => <Why />
    | ["new"] => <NewPoll notify />
    | ["manage-poll", manageToken] => <ManagePollPage manageToken />
    | ["manage-poll", manageToken, "edit-results"] =>
      <EditResultsPage notify manageToken />
    | ["take-poll", pollId] => <TakePollPage notify id=pollId />
    | ["results", pollId] => <PollResultsPage id=pollId />
    | _ => <NotFound />
    };

  <Layout notifications> body </Layout>;
};