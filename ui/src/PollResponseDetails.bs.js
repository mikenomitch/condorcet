// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var List = require("bs-platform/lib/js/list.js");
var $$Array = require("bs-platform/lib/js/array.js");
var React = require("react");
var R$Condorcet = require("./lib/R.bs.js");

function PollResponseDetails(Props) {
  var result = Props.result;
  var renderResponseCount = function (count) {
    if (count !== 0) {
      if (count !== 1) {
        return React.createElement("h5", undefined, R$Condorcet.s(String(count) + " responses:"));
      } else {
        return React.createElement("h5", undefined, R$Condorcet.s("1 response from: "));
      }
    } else {
      return React.createElement("h5", undefined, R$Condorcet.s("No responses yet"));
    }
  };
  var renderResponseNames = function (responses) {
    if (responses) {
      return React.createElement("p", undefined, R$Condorcet.s($$Array.of_list(List.map((function (r) {
                                  return r.name;
                                }), responses)).join(", ")));
    } else {
      return null;
    }
  };
  var renderComment = function (r) {
    var match = r.comment;
    if (match !== undefined) {
      return React.createElement("p", {
                  key: r.id
                }, React.createElement("span", {
                      className: "fw-normal"
                    }, R$Condorcet.s(r.name + ":  ")), R$Condorcet.s(match));
    } else {
      return null;
    }
  };
  var renderResponseComments = function (responses) {
    var with_comment = List.filter((function (r) {
              return r.comment !== undefined;
            }))(responses);
    if (with_comment) {
      return React.createElement("div", undefined, React.createElement("h5", undefined, R$Condorcet.s("Comments:")), $$Array.of_list(List.map(renderComment, with_comment)));
    } else {
      return null;
    }
  };
  return React.createElement("div", {
              className: "responses-holder"
            }, renderResponseCount(result.responseCount), renderResponseNames(result.responses), renderResponseComments(result.responses));
}

var make = PollResponseDetails;

exports.make = make;
/* react Not a pure module */