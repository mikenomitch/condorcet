[@react.component]
let make = () => {
  let url = ReasonReact.Router.useUrl();

  let body =
    switch (url.path) {
    | [] => <Home />
    | ["new"] => <NewPoll />
    | ["why"] => <Why />
    | ["manage-poll", manageToken] => <ManagePollPage manageToken />
    | ["take-poll", pollId] => <TakePollPage id=pollId />
    | ["results", pollId] => <PollResultsPage id=pollId />
    | _ => <NotFound />
    };

  <Layout> body </Layout>;
};