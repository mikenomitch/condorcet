// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var List = require("bs-platform/lib/js/list.js");
var $$Array = require("bs-platform/lib/js/array.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var Caml_array = require("bs-platform/lib/js/caml_array.js");
var R$Condorcet = require("./R.bs.js");
var Api$Condorcet = require("./Api.bs.js");
var Input$Condorcet = require("./Input.bs.js");
var ReasonReactRouter = require("reason-react/src/ReasonReactRouter.js");

function TakePoll(Props) {
  var poll = Props.poll;
  var match = React.useState((function () {
          return poll.choices;
        }));
  var changeOrdering = match[1];
  var choiceOrder = match[0];
  var match$1 = React.useState((function () {
          return "";
        }));
  var changeName = match$1[1];
  var name = match$1[0];
  var move = function (amount, idx) {
    var newChoices = $$Array.of_list(choiceOrder);
    var moving = Caml_array.caml_array_get(newChoices, idx);
    var replacing = Caml_array.caml_array_get(newChoices, idx + amount | 0);
    Caml_array.caml_array_set(newChoices, idx, replacing);
    Caml_array.caml_array_set(newChoices, idx + amount | 0, moving);
    var newList = $$Array.to_list(newChoices);
    return Curry._1(changeOrdering, (function (param) {
                  return newList;
                }));
  };
  var response = {
    id: undefined,
    name: name,
    order: choiceOrder
  };
  var submitChoices = function (param) {
    var match = poll.id;
    if (match !== undefined) {
      var id = match;
      Api$Condorcet.submitPoll(id, response).then((function (param) {
              return Promise.resolve(ReasonReactRouter.push("/results/" + id));
            }));
    } else {
      Promise.resolve(/* () */0);
    }
    return /* () */0;
  };
  var renderChoice = function (idx, choice) {
    var moveChoiceUp = function (param) {
      return move(-1, idx);
    };
    var moveChoiceDown = function (param) {
      return move(1, idx);
    };
    return React.createElement("div", {
                key: choice,
                className: "take-choice"
              }, React.createElement("p", {
                    className: "take-choice-text"
                  }, R$Condorcet.s(choice)), React.createElement("div", {
                    className: "take-choice-btn"
                  }, React.createElement("button", {
                        className: "button button-sm",
                        disabled: idx === 0,
                        onClick: moveChoiceUp
                      }, R$Condorcet.s("Up"))), React.createElement("div", {
                    className: "take-choice-btn"
                  }, React.createElement("button", {
                        className: "button button-sm",
                        disabled: (idx + 1 | 0) === List.length(choiceOrder),
                        onClick: moveChoiceDown
                      }, R$Condorcet.s("Down"))));
  };
  return React.createElement("div", {
              className: "page"
            }, React.createElement("h3", undefined, R$Condorcet.s(poll.question)), React.createElement("div", {
                  className: "take-poll-choice-list"
                }, $$Array.of_list(List.mapi(renderChoice, choiceOrder))), React.createElement("br", undefined), React.createElement("br", undefined), React.createElement(Input$Condorcet.make, {
                  placeholder: "...",
                  value: name,
                  onChange: (function ($$event) {
                      return Curry._1(changeName, $$event.target.value);
                    }),
                  label: "Your Name:"
                }), React.createElement("br", undefined), React.createElement("br", undefined), React.createElement("div", {
                  className: "centered"
                }, React.createElement("button", {
                      className: "button button-mdlg",
                      onClick: submitChoices
                    }, R$Condorcet.s("Submit"))));
}

var make = TakePoll;

exports.make = make;
/* react Not a pure module */
