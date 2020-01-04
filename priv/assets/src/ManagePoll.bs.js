// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var React = require("react");
var R$Condorcet = require("./R.bs.js");
var ReasonReactRouter = require("reason-react/src/ReasonReactRouter.js");
var PollResults$Condorcet = require("./PollResults.bs.js");

function ManagePoll(Props) {
  var result = Props.result;
  var match = result.poll.id;
  var tmp;
  if (match !== undefined) {
    var id = match;
    tmp = React.createElement("button", {
          onClick: (function (param) {
              return ReasonReactRouter.push("/take-poll/" + id);
            })
        }, R$Condorcet.s("Take the Poll Yourself"));
  } else {
    tmp = null;
  }
  var match$1 = result.poll.id;
  var match$2 = result.poll.manageToken;
  return React.createElement("div", undefined, React.createElement("h1", undefined, R$Condorcet.s("Poll: " + result.poll.question)), tmp, React.createElement("div", undefined, React.createElement("h2", undefined, R$Condorcet.s("Links")), match$1 !== undefined ? React.createElement("p", undefined, R$Condorcet.s("Link to take poll: localhost:1234/take-poll/" + match$1)) : null, match$2 !== undefined ? React.createElement("p", undefined, R$Condorcet.s("Link to take poll: localhost:1234/take-poll/" + match$2)) : null), React.createElement(PollResults$Condorcet.make, {
                  result: result
                }));
}

var make = ManagePoll;

exports.make = make;
/* react Not a pure module */
