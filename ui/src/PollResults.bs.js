// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var List = require("bs-platform/lib/js/list.js");
var $$Array = require("bs-platform/lib/js/array.js");
var React = require("react");
var R$Condorcet = require("./R.bs.js");

function PollResults(Props) {
  var result = Props.result;
  var renderWinners = function (winnersList) {
    return React.createElement("b", undefined, R$Condorcet.s($$Array.of_list(winnersList).join(", ")));
  };
  var renderResponseCount = function (count) {
    if (count !== 0) {
      if (count !== 1) {
        return React.createElement("p", undefined, R$Condorcet.s(String(count) + " responses from:"));
      } else {
        return React.createElement("p", undefined, R$Condorcet.s("1 response from: "));
      }
    } else {
      return React.createElement("p", undefined, R$Condorcet.s("No responses yet"));
    }
  };
  var renderResponseNames = function (names) {
    if (names) {
      return React.createElement("p", undefined, R$Condorcet.s($$Array.of_list(names).join(", ")));
    } else {
      return null;
    }
  };
  var match = result.winners;
  var tmp;
  if (match !== undefined) {
    var winnerMap = match;
    var match$1 = List.length(winnerMap.ranked) > 1;
    var rankedString = match$1 ? "The ranked choice winners are: " : "The ranked choice winner is: ";
    var match$2 = List.length(winnerMap.borda) > 1;
    var bordaString = match$2 ? "The borda count winners are: " : "The borda count winner is: ";
    var match$3 = List.length(winnerMap.plurality) > 1;
    var pluralityString = match$3 ? "The plurality winners are: " : "The plurality winner is: ";
    tmp = React.createElement("div", undefined, React.createElement("p", undefined, R$Condorcet.s(rankedString), renderWinners(winnerMap.ranked)), React.createElement("p", undefined, R$Condorcet.s(bordaString), renderWinners(winnerMap.borda)), React.createElement("p", undefined, R$Condorcet.s(pluralityString), renderWinners(winnerMap.plurality)));
  } else {
    tmp = null;
  }
  return React.createElement("div", undefined, tmp, React.createElement("div", {
                  className: "responses-holder"
                }, renderResponseCount(result.responseCount), renderResponseNames(result.names)));
}

var make = PollResults;

exports.make = make;
/* react Not a pure module */
