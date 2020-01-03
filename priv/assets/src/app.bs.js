// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var React = require("react");
var Home$Condorcet = require("./Home.bs.js");
var Layout$Condorcet = require("./Layout.bs.js");
var NewPoll$Condorcet = require("./NewPoll.bs.js");
var ReasonReactRouter = require("reason-react/src/ReasonReactRouter.js");
var NotFound$Condorcet = require("./NotFound.bs.js");
var TakePollPage$Condorcet = require("./TakePollPage.bs.js");
var ManagePollPage$Condorcet = require("./ManagePollPage.bs.js");
var PollResultsPage$Condorcet = require("./PollResultsPage.bs.js");

function App(Props) {
  var url = ReasonReactRouter.useUrl(undefined, /* () */0);
  var match = url.path;
  var body;
  var exit = 0;
  if (match) {
    switch (match[0]) {
      case "manage-poll" :
          var match$1 = match[1];
          if (match$1 && !match$1[1]) {
            body = React.createElement(ManagePollPage$Condorcet.make, {
                  id: match$1[0]
                });
          } else {
            exit = 1;
          }
          break;
      case "new" :
          if (match[1]) {
            exit = 1;
          } else {
            body = React.createElement(NewPoll$Condorcet.make, { });
          }
          break;
      case "results" :
          var match$2 = match[1];
          if (match$2 && !match$2[1]) {
            body = React.createElement(PollResultsPage$Condorcet.make, {
                  id: match$2[0]
                });
          } else {
            exit = 1;
          }
          break;
      case "take-poll" :
          var match$3 = match[1];
          if (match$3 && !match$3[1]) {
            body = React.createElement(TakePollPage$Condorcet.make, {
                  id: match$3[0]
                });
          } else {
            exit = 1;
          }
          break;
      default:
        exit = 1;
    }
  } else {
    body = React.createElement(Home$Condorcet.make, { });
  }
  if (exit === 1) {
    body = React.createElement(NotFound$Condorcet.make, { });
  }
  return React.createElement(Layout$Condorcet.make, {
              children: body
            });
}

var make = App;

exports.make = make;
/* react Not a pure module */