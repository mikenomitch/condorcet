// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var React = require("react");
var R$Condorcet = require("./R.bs.js");
var Style$Condorcet = require("./Style.bs.js");
var ReasonReactRouter = require("reason-react/src/ReasonReactRouter.js");

function Layout(Props) {
  var children = Props.children;
  return React.createElement("div", undefined, React.createElement("div", {
                  style: Style$Condorcet.header,
                  onClick: (function (param) {
                      return ReasonReactRouter.push("/");
                    })
                }, R$Condorcet.s("Condorcet")), children);
}

var make = Layout;

exports.make = make;
/* react Not a pure module */