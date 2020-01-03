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
              return ReasonReactRouter.push("/take-poll/" + String(id));
            })
        }, R$Condorcet.s("Take the Poll Yourself"));
  } else {
    tmp = null;
  }
  return React.createElement("div", undefined, React.createElement("h1", undefined, R$Condorcet.s("Poll: " + result.poll.question)), tmp, React.createElement("div", undefined, React.createElement("h2", undefined, R$Condorcet.s("Links")), React.createElement("p", undefined, R$Condorcet.s("Link to take poll: http://zombo.com/poll/12345")), React.createElement("p", undefined, R$Condorcet.s("Save this link to manage the poll in the future: http://zombo.com/poll/12345/manage/token"))), React.createElement(PollResults$Condorcet.make, {
                  result: result
                }));
}

var make = ManagePoll;

exports.make = make;
/* react Not a pure module */