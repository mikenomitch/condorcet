[@bs.val] external setTimeout: (unit => unit, int) => float = "setTimeout";

[@react.component]
let make = () => {
  let (notifications, setNotifications) = React.useState(() => []);
  let addError = text => {
    let notif: Notifications.notification = {t: "error", text};
    setNotifications(_ => [notif]);
    setTimeout(() => {setNotifications(_state => [])}, 3000) |> ignore;
  };

  let url = ReasonReact.Router.useUrl();

  let body =
    switch (url.path) {
    | [] => <Home />
    | ["why"] => <Why />
    | ["new"] => <NewPoll addError />
    | ["manage-poll", manageToken] => <ManagePollPage manageToken />
    | ["manage-poll", manageToken, "edit-choices"] =>
      <EditChoicesPage manageToken />
    | ["take-poll", pollId] => <TakePollPage addError id=pollId />
    | ["results", pollId] => <PollResultsPage id=pollId />
    | _ => <NotFound />
    };

  <Layout notifications> body </Layout>;
};