[@react.component]
let make = () => {
  <div className="page">
    <h3 className="centered"> {R.s("Why alternative elections?")} </h3>
    <h4 className="centered"> {R.s("The problem with plurality voting")} </h4>
    <p>
      {R.s(
         "Deciding between two options is often simple, as you can just select the option with the most votes.
         Once more than two options are included, it become significantly harder to determine the ideal winner.
         ",
       )}
    </p>
    <p>
      {R.s(
         "
         For example, imagine that a group of coworkers is deciding where to go for an off-site and
         four options are presented: San Diego, Miami, Park City, and Aspen.
         They take a poll and the results come back:
         ",
       )}
    </p>
    <div>
      <i> <b> {R.s("Aspen: ")} </b> </i>
      {R.s("10 votes")}
      <br />
      <i> <b> {R.s("Miami: ")} </b> </i>
      {R.s("8 votes")}
      <br />
      <i> <b> {R.s("San Diego: ")} </b> </i>
      {R.s("7 votes")}
      <br />
      <i> <b> {R.s("Park City: ")} </b> </i>
      {R.s("2 votes")}
      <br />
    </div>
    <p>
      {R.s(
         "
         Aspen wins, but there is an issue. If you were to re-poll the group,
         but instead ask \"Do you want to go to the beach or to the mountains?\",
         the beach would actually win:
         ",
       )}
    </p>
    <div>
      <i> <b> {R.s("Beach (Miami or San Diego): ")} </b> </i>
      {R.s("15 votes")}
      <br />
      <i> <b> {R.s("Mountains (Aspen or Park City): ")} </b> </i>
      {R.s("12 votes")}
      <br />
    </div>
    <p>
      {R.s(
         "
         The way we present options can affect the outcome.
         So, how can we decide between multiple options in a fair way?
         ",
       )}
    </p>
    <p>
      {R.s(
         "
          Poller.io uses a few methods to improve the results.
         ",
       )}
    </p>
    <h4 id="alternative-methods" className="centered">
      {R.s("The alternative methods")}
    </h4>
    <p>
      <b> {R.s("Instant Runoff Voting (IRV):")} </b>
      <br />
      {R.s("In ")}
      <a href="https://en.wikipedia.org/wiki/Instant-runoff_voting">
        {R.s("Instant Runoff Voting")}
      </a>
      {R.s(
         ", voters rank each option. If no single option has a majority of
        first place votes, the option with the lowest number of first place votes is removed from the rankings,
        and the process is run again. This continues until a single option has a majority of first place
        votes.
      ",
       )}
    </p>
    <p>
      {R.s(
         "
          Instant Runoff Voting is sometimes refered to as the \"alternative vote\", \"preferential voting\", or\"ranked choice voting\".
        ",
       )}
    </p>
    <p>
      <b> {R.s("Condorcet Method:")} </b>
      <br />
      {R.s("Using  ")}
      <a href="https://en.wikipedia.org/wiki/Condorcet_method">
        {R.s("the Condorcet Method")}
      </a>
      {R.s(
         ", the list of ranked options gets converted into a series
      of head to head polls. If any single option can beat every other option when compared head
      to head, that option is the \"Condorcet Winner\". Unfortunately, not every election will
      have a Condorcet Winner.
      ",
       )}
    </p>
    <p>
      <b> {R.s("Borda Count:")} </b>
      <br />
      {R.s("In a ")}
      <a href="https://en.wikipedia.org/wiki/Borda_count">
        {R.s("Borda Count")}
      </a>
      {R.s(
         ", voters rank each option and points are distributed to each according to their rank.
         If there are 3 options, the option in first place on a ballot gets 2 points,
         the option in second gets 1 point, and the option in last place gets 0 points.
         Whichever option has the most points across all ballots wins.
         ",
       )}
    </p>
    <p>
      {R.s("Unfortunately, ")}
      <a href="https://en.wikipedia.org/wiki/Arrow%27s_impossibility_theorem">
        {R.s("none of these methods are perfect")}
      </a>
      {R.s(
         ", but with all methods run simultaneously, hopefully you can make
         the best choice for your specific situation.",
       )}
    </p>
    <p>
      {R.s("If you prefer learning via video, CPG Grey has a ")}
      <a href="https://www.cgpgrey.com/politics-in-the-animal-kingdom">
        {R.s("YouTube series on this topic")}
      </a>
      {R.s(" that is worth watching.")}
    </p>
    <h4 className="centered"> {R.s("Ready to get started?")} </h4>
    <div className="centered">
      <button
        className="button button-mdlg"
        onClick={_ => ReasonReactRouter.push("/new")}>
        {R.s("Create a Poll")}
      </button>
    </div>
    <h4 className="centered"> {R.s("About the site")} </h4>
    <p>
      {R.s(
         "This site was made to be the simplest way to make group decisions.
          I really enjoy getting feedback, so feel free to email me at poller(at)mikenomitch(dot)com.",
       )}
    </p>
    <p>
      {R.s("Check out ")}
      <a href="https://www.fairvote.org/"> {R.s("FairVote")} </a>
      {R.s(
         " if you would like to see alternative voting in American politics.",
       )}
    </p>
    <p>
      {R.s("If you prefer more direct way to do good, consider donating to ")}
      <a href="https://secure.givewell.org/"> {R.s("GiveWell")} </a>
      {R.s(
         ". An organization that specializes in finding the most effective uses for charitable donations.",
       )}
    </p>
    <br />
  </div>;
};