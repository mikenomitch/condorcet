// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var React = require("react");
var R$Condorcet = require("./R.bs.js");
var ReasonReactRouter = require("reason-react/src/ReasonReactRouter.js");

function Home(Props) {
  return React.createElement("div", undefined, React.createElement("h1", undefined, R$Condorcet.s("Condorcet Home")), React.createElement("button", {
                  onClick: (function (param) {
                      return ReasonReactRouter.push("/new");
                    })
                }, R$Condorcet.s("Create a Poll")));
}

var make = Home;

exports.make = make;
/* react Not a pure module */
