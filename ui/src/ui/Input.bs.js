// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var React = require("react");
var Caml_option = require("bs-platform/lib/js/caml_option.js");
var R$Condorcet = require("../lib/R.bs.js");

function Input(Props) {
  var placeholder = Props.placeholder;
  var value = Props.value;
  var onChange = Props.onChange;
  var $staropt$star = Props.focusOnRender;
  var label = Props.label;
  var focusOnRender = $staropt$star !== undefined ? $staropt$star : false;
  var inputRef = React.useRef(undefined);
  React.useEffect((function () {
          if (focusOnRender) {
            var current = inputRef.current;
            if (current !== undefined) {
              Caml_option.valFromOption(current).focus();
            }
            
          }
          return ;
        }), ([]));
  var input = React.createElement("input", {
        ref: (function (elem) {
            inputRef.current = (elem == null) ? undefined : Caml_option.some(elem);
            return /* () */0;
          }),
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
