[@react.component]
let make = () => {
  let url = ReasonReact.Router.useUrl();

  let body =
    switch (url.path) {
    | [] => <Home />
    | ["new"] => <NewPoll />
    | ["manage-poll", pollId] => <ManagePollPage id=pollId />
    | ["take-poll", pollId] => <TakePollPage id=pollId />
    | ["results", pollId] => <PollResultsPage id=pollId />
    | _ => <NotFound />
    };

  <Layout> body </Layout>;
};