// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var React = require("react");
var R$Condorcet = require("./R.bs.js");

function Input(Props) {
  var placeholder = Props.placeholder;
  var value = Props.value;
  var onChange = Props.onChange;
  var label = Props.label;
  var input = React.createElement("input", {
        className: "input input-full-width",
        placeholder: placeholder,
        value: value,
        onChange: onChange
      });
  if (label !== undefined) {
    return React.createElement("div", undefined, React.createElement("label", undefined, R$Condorcet.s(label)), React.createElement("div", {
                    className: "m-t-sm"
                  }, input));
  } else {
    return input;
  }
}

var make = Input;

exports.make = make;
/* react Not a pure module */
