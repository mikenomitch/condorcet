// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var React = require("react");
var R$Condorcet = require("./R.bs.js");
var ReasonReactRouter = require("reason-react/src/ReasonReactRouter.js");

function Layout(Props) {
  var children = Props.children;
  return React.createElement("div", undefined, React.createElement("div", {
                  className: "header",
                  onClick: (function (param) {
                      return ReasonReactRouter.push("/");
                    })
                }, R$Condorcet.s("Condorcet.io")), React.createElement("div", {
                  className: "content"
                }, children));
}

var make = Layout;

exports.make = make;
/* react Not a pure module */