// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var Fetch = require("bs-fetch/src/Fetch.js");
var Caml_option = require("bs-platform/lib/js/caml_option.js");
var Data$Condorcet = require("./Data.bs.js");

function fetchPoll(id, cb) {
  fetch("http://localhost:4000/api/v1/polls/" + id).then((function (prim) {
            return prim.json();
          })).then((function (json) {
          var poll = Data$Condorcet.Decode.dPoll(json);
          return Promise.resolve(Curry._1(cb, (function (param) {
                            return poll;
                          })));
        }));
  return /* () */0;
}

function fetchResult(id, cb) {
  fetch("http://localhost:4000/api/v1/polls/" + (id + "/results")).then((function (prim) {
            return prim.json();
          })).then((function (json) {
          var result = Data$Condorcet.Decode.dResult(json);
          return Promise.resolve(Curry._1(cb, (function (param) {
                            return result;
                          })));
        }));
  return /* () */0;
}

function createPoll(poll) {
  var payload = Data$Condorcet.encodePollPost(poll);
  return fetch("http://localhost:4000/api/v1/polls/", Fetch.RequestInit.make(/* Post */2, {
                      "Content-Type": "application/json"
                    }, Caml_option.some(JSON.stringify(payload)), undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined)(/* () */0)).then((function (prim) {
                return prim.json();
              }));
}

function submitPoll(id, response) {
  var payload = Data$Condorcet.encodeResponsePost(response);
  return fetch("http://localhost:4000/api/v1/polls/" + (id + "/respond"), Fetch.RequestInit.make(/* Post */2, {
                      "Content-Type": "application/json"
                    }, Caml_option.some(JSON.stringify(payload)), undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined)(/* () */0)).then((function (prim) {
                return prim.json();
              }));
}

exports.fetchPoll = fetchPoll;
exports.fetchResult = fetchResult;
exports.createPoll = createPoll;
exports.submitPoll = submitPoll;
/* No side effect */
