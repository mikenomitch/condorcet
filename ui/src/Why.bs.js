// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var React = require("react");
var R$Condorcet = require("./lib/R.bs.js");
var ReasonReactRouter = require("reason-react/src/ReasonReactRouter.js");

function Why(Props) {
  return React.createElement("div", {
              className: "page"
            }, React.createElement("h3", {
                  className: "centered"
                }, R$Condorcet.s("Why alternative elections?")), React.createElement("h4", {
                  className: "centered"
                }, R$Condorcet.s("The problem with plurality voting")), React.createElement("p", undefined, R$Condorcet.s("Deciding between two options is often simple, as you can just select the option with the most votes.\n         Once more than two options are included, it become significantly harder to determine the ideal winner.\n         ")), React.createElement("p", undefined, R$Condorcet.s("\n         For example, imagine that a group of coworkers is deciding where to go for an off-site and\n         four options are presented: San Diego, Miami, Park City, and Aspen.\n         They take a poll and the results come back:\n         ")), React.createElement("div", undefined, React.createElement("i", undefined, React.createElement("b", undefined, R$Condorcet.s("Aspen: "))), R$Condorcet.s("10 votes"), React.createElement("br", undefined), React.createElement("i", undefined, React.createElement("b", undefined, R$Condorcet.s("Miami: "))), R$Condorcet.s("8 votes"), React.createElement("br", undefined), React.createElement("i", undefined, React.createElement("b", undefined, R$Condorcet.s("San Diego: "))), R$Condorcet.s("7 votes"), React.createElement("br", undefined), React.createElement("i", undefined, React.createElement("b", undefined, R$Condorcet.s("Park City: "))), R$Condorcet.s("2 votes"), React.createElement("br", undefined)), React.createElement("p", undefined, R$Condorcet.s("\n         Aspen wins, but there is an issue. If you were to re-poll the group,\n         but instead ask \"Do you want to go to the beach or to the mountains?\",\n         the beach would actually win:\n         ")), React.createElement("div", undefined, React.createElement("i", undefined, React.createElement("b", undefined, R$Condorcet.s("Beach (Miami or San Diego): "))), R$Condorcet.s("15 votes"), React.createElement("br", undefined), React.createElement("i", undefined, React.createElement("b", undefined, R$Condorcet.s("Mountains (Aspen or Park City): "))), R$Condorcet.s("12 votes"), React.createElement("br", undefined)), React.createElement("p", undefined, R$Condorcet.s("\n         The way we present options can affect the outcome.\n         So, how can we decide between multiple options in a fair way?\n         ")), React.createElement("p", undefined, R$Condorcet.s("\n          Poller.io uses a few methods to improve the results.\n         ")), React.createElement("h4", {
                  className: "centered",
                  id: "alternative-methods"
                }, R$Condorcet.s("The alternative methods")), React.createElement("p", undefined, React.createElement("b", undefined, R$Condorcet.s("Instant Runoff Voting (IRV):")), React.createElement("br", undefined), R$Condorcet.s("In "), React.createElement("a", {
                      href: "https://en.wikipedia.org/wiki/Instant-runoff_voting"
                    }, R$Condorcet.s("Instant Runoff Voting")), R$Condorcet.s(", voters rank each option. If no single option has a majority of\n        first place votes, the option with the lowest number of first place votes is removed from the rankings,\n        and the process is run again. This continues until a single option has a majority of first place\n        votes.\n      ")), React.createElement("p", undefined, R$Condorcet.s("\n          Instant Runoff Voting is sometimes refered to as the \"alternative vote\", \"preferential voting\", or\"ranked choice voting\".\n        ")), React.createElement("p", undefined, React.createElement("b", undefined, R$Condorcet.s("Condorcet Method:")), React.createElement("br", undefined), R$Condorcet.s("Using  "), React.createElement("a", {
                      href: "https://en.wikipedia.org/wiki/Condorcet_method"
                    }, R$Condorcet.s("the Condorcet Method")), R$Condorcet.s(", the list of ranked options gets converted into a series\n      of head to head polls. If any single option can beat every other option when compared head\n      to head, that option is the \"Condorcet Winner\". Unfortunately, not every election will\n      have a Condorcet Winner.\n      ")), React.createElement("p", undefined, React.createElement("b", undefined, R$Condorcet.s("Borda Count:")), React.createElement("br", undefined), R$Condorcet.s("In a "), React.createElement("a", {
                      href: "https://en.wikipedia.org/wiki/Borda_count"
                    }, R$Condorcet.s("Borda Count")), R$Condorcet.s(", voters rank each option and points are distributed to each according to their rank.\n         If there are 3 options, the option in first place on a ballot gets 2 points,\n         the option in second gets 1 point, and the option in last place gets 0 points.\n         Whichever option has the most points across all ballots wins.\n         ")), React.createElement("p", undefined, R$Condorcet.s("Unfortunately, "), React.createElement("a", {
                      href: "https://en.wikipedia.org/wiki/Arrow%27s_impossibility_theorem"
                    }, R$Condorcet.s("none of these methods are perfect")), R$Condorcet.s(", but with all methods run simultaneously, hopefully you can make\n         the best choice for your specific situation.")), React.createElement("p", undefined, R$Condorcet.s("If you prefer learning via video, CPG Grey has a "), React.createElement("a", {
                      href: "https://www.cgpgrey.com/politics-in-the-animal-kingdom"
                    }, R$Condorcet.s("YouTube series on this topic")), R$Condorcet.s(" that is worth watching.")), React.createElement("h4", {
                  className: "centered"
                }, R$Condorcet.s("Ready to get started?")), React.createElement("div", {
                  className: "centered"
                }, React.createElement("button", {
                      className: "button button-mdlg",
                      onClick: (function (param) {
                          return ReasonReactRouter.push("/new");
                        })
                    }, R$Condorcet.s("Create a Poll"))), React.createElement("h4", {
                  className: "centered"
                }, R$Condorcet.s("About the site")), React.createElement("p", undefined, R$Condorcet.s("This site was made to be the simplest way to make group decisions.\n          I really enjoy getting feedback, so feel free to email me at poller(at)mikenomitch(dot)com.")), React.createElement("p", undefined, R$Condorcet.s("Check out "), React.createElement("a", {
                      href: "https://www.fairvote.org/"
                    }, R$Condorcet.s("FairVote")), R$Condorcet.s(" if you would like to see alternative voting in American politics.")), React.createElement("p", undefined, R$Condorcet.s("If you prefer more direct way to do good, consider donating to "), React.createElement("a", {
                      href: "https://secure.givewell.org/"
                    }, R$Condorcet.s("GiveWell")), R$Condorcet.s(". An organization that specializes in finding the most effective uses of charitable donations.")), React.createElement("br", undefined));
}

var make = Why;

exports.make = make;
/* react Not a pure module */
