// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var R$Condorcet = require("./R.bs.js");

function Ordinal(Props) {
  var num = Props.num;
  switch (num) {
    case 0 :
        return R$Condorcet.s("0th");
    case 1 :
        return R$Condorcet.s("1st");
    case 2 :
        return R$Condorcet.s("2nd");
    case 3 :
        return R$Condorcet.s("3rd");
    default:
      return R$Condorcet.s(String(num) + "th");
  }
}

var make = Ordinal;

exports.make = make;
/* No side effect */
