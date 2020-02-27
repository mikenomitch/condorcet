// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var React = require("react");
var Api$Condorcet = require("./lib/Api.bs.js");
var TakePoll$Condorcet = require("./TakePoll.bs.js");

function TakePollPage(Props) {
  var id = Props.id;
  var notify = Props.notify;
  var match = React.useState((function () {
          return ;
        }));
  var setPoll = match[1];
  var poll = match[0];
  React.useEffect((function () {
          Api$Condorcet.fetchPoll(id, setPoll);
          return ;
        }), ([]));
  if (poll !== undefined) {
    return React.createElement(TakePoll$Condorcet.make, {
                poll: poll,
                notify: notify
              });
  } else {
    return null;
  }
}

var make = TakePollPage;

exports.make = make;
/* react Not a pure module */
