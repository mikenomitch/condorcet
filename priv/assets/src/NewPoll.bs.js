// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var List = require("bs-platform/lib/js/list.js");
var $$Array = require("bs-platform/lib/js/array.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var Caml_array = require("bs-platform/lib/js/caml_array.js");
var R$Condorcet = require("./R.bs.js");
var Api$Condorcet = require("./Api.bs.js");
var Data$Condorcet = require("./Data.bs.js");
var RList$Rationale = require("rationale/src/RList.js");
var ReasonReactRouter = require("reason-react/src/ReasonReactRouter.js");

function NewPoll(Props) {
  var match = React.useState((function () {
          return {
                  id: 1,
                  question: "",
                  choices: /* :: */[
                    "",
                    /* :: */[
                      "",
                      /* :: */[
                        "",
                        /* :: */[
                          "",
                          /* [] */0
                        ]
                      ]
                    ]
                  ]
                };
        }));
  var setPoll = match[1];
  var poll = match[0];
  var addChoice = function (param) {
    return Curry._1(setPoll, (function (param) {
                  return {
                          id: poll.id,
                          question: poll.question,
                          choices: List.append(poll.choices, /* :: */[
                                "",
                                /* [] */0
                              ])
                        };
                }));
  };
  var savePoll = function (param) {
    Api$Condorcet.createPoll(poll).then((function (json) {
              return Promise.resolve(Data$Condorcet.Decode.dPoll(json));
            })).then((function (poll) {
            var match = poll.id;
            if (match !== undefined) {
              return Promise.resolve(ReasonReactRouter.push("/manage-poll/" + String(match)));
            } else {
              return Promise.resolve(ReasonReactRouter.push("/manage-poll/1"));
            }
          }));
    return /* () */0;
  };
  var renderChoice = function (idx, answer) {
    return React.createElement("div", {
                key: String(idx)
              }, React.createElement("input", {
                    placeholder: "Choice...",
                    value: answer,
                    onChange: (function ($$event) {
                        var newChoice = $$event.target.value;
                        var idx$1 = idx;
                        var newChoices = $$Array.of_list(poll.choices);
                        Caml_array.caml_array_set(newChoices, idx$1, newChoice);
                        var newList = $$Array.to_list(newChoices);
                        return Curry._1(setPoll, (function (param) {
                                      return {
                                              id: poll.id,
                                              question: poll.question,
                                              choices: newList
                                            };
                                    }));
                      })
                  }), React.createElement("button", {
                    onClick: (function (param) {
                        var idx$1 = idx;
                        var newChoices = RList$Rationale.remove(idx$1, 1, poll.choices);
                        console.log("whoa");
                        return Curry._1(setPoll, (function (param) {
                                      return {
                                              id: poll.id,
                                              question: poll.question,
                                              choices: newChoices
                                            };
                                    }));
                      })
                  }, R$Condorcet.s("Remove")));
  };
  return React.createElement("div", undefined, React.createElement("h2", undefined, R$Condorcet.s("Make a Poll")), React.createElement("div", undefined, React.createElement("input", {
                      placeholder: "Question...",
                      value: poll.question,
                      onChange: (function ($$event) {
                          var question = $$event.target.value;
                          return Curry._1(setPoll, (function (param) {
                                        return {
                                                id: poll.id,
                                                question: question,
                                                choices: poll.choices
                                              };
                                      }));
                        })
                    })), React.createElement("br", undefined), React.createElement("br", undefined), React.createElement("div", undefined, $$Array.of_list(List.mapi(renderChoice, poll.choices))), React.createElement("br", undefined), React.createElement("br", undefined), React.createElement("div", undefined, React.createElement("button", {
                      onClick: addChoice
                    }, R$Condorcet.s("+"))), React.createElement("br", undefined), React.createElement("br", undefined), React.createElement("div", undefined, React.createElement("button", {
                      onClick: savePoll
                    }, R$Condorcet.s("Save"))));
}

var RList = /* alias */0;

var make = NewPoll;

exports.RList = RList;
exports.make = make;
/* react Not a pure module */
