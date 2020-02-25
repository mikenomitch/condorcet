// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var List = require("bs-platform/lib/js/list.js");
var $$Array = require("bs-platform/lib/js/array.js");
var Curry = require("bs-platform/lib/js/curry.js");
var Fetch = require("bs-fetch/src/Fetch.js");
var Pervasives = require("bs-platform/lib/js/pervasives.js");
var Caml_option = require("bs-platform/lib/js/caml_option.js");
var Data$Condorcet = require("./Data.bs.js");
var Constants$Condorcet = require("./Constants.bs.js");

var baseUrl = Constants$Condorcet.protocol + ("://" + Constants$Condorcet.host);

function fetchPoll(id, cb) {
  fetch(baseUrl + ("/api/v1/polls/" + id)).then((function (prim) {
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
  fetch(baseUrl + ("/api/v1/polls/" + (id + "/results"))).then((function (prim) {
            return prim.json();
          })).then((function (json) {
          var result = Data$Condorcet.Decode.dResult(json);
          return Promise.resolve(Curry._1(cb, (function (param) {
                            return result;
                          })));
        }));
  return /* () */0;
}

function fetchManageResult(manageToken, cb) {
  fetch(baseUrl + ("/api/v1/polls/" + (manageToken + "/manage"))).then((function (prim) {
            return prim.json();
          })).then((function (json) {
          var result = Data$Condorcet.Decode.dResult(json);
          return Promise.resolve(Curry._1(cb, (function (param) {
                            return result;
                          })));
        }));
  return /* () */0;
}

function createPoll(poll, addError) {
  var payload = Data$Condorcet.encodePollPost(poll);
  return fetch(baseUrl + "/api/v1/polls/", Fetch.RequestInit.make(/* Post */2, {
                        "Content-Type": "application/json"
                      }, Caml_option.some(JSON.stringify(payload)), undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined)(/* () */0)).then((function (prim) {
                  return prim.json();
                })).then((function (json) {
                var match = Curry._1(Data$Condorcet.Decode.dPollOrErrors, json);
                if (match.tag) {
                  return Promise.resolve(match[0]);
                } else {
                  var errors = match[0];
                  var match$1 = errors.errors.question;
                  var questionErrors = match$1 !== undefined ? List.map((function (s) {
                            return "Question " + s;
                          }), match$1) : /* [] */0;
                  var match$2 = errors.errors.choices;
                  var choiceErrors = match$2 !== undefined ? match$2 : /* [] */0;
                  var showErrors = $$Array.of_list(Pervasives.$at(choiceErrors, questionErrors)).join(", ");
                  Curry._1(addError, showErrors);
                  return Promise.resolve(undefined);
                }
              }));
}

function submitPoll(id, response) {
  var payload = Data$Condorcet.encodeResponsePost(response);
  return fetch(baseUrl + ("/api/v1/polls/" + (id + "/respond")), Fetch.RequestInit.make(/* Post */2, {
                        "Content-Type": "application/json"
                      }, Caml_option.some(JSON.stringify(payload)), undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined)(/* () */0)).then((function (prim) {
                  return prim.json();
                })).then((function (json) {
                return Promise.resolve(Curry._1(Data$Condorcet.Decode.dResponseOrErrors, json));
              }));
}

function removeChoice(manageToken, choice) {
  var payload = Data$Condorcet.encodeChoice(choice);
  return fetch(baseUrl + ("/api/v1/polls/" + (manageToken + "/remove_choice")), Fetch.RequestInit.make(/* Post */2, {
                        "Content-Type": "application/json"
                      }, Caml_option.some(JSON.stringify(payload)), undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined)(/* () */0)).then((function (prim) {
                  return prim.json();
                })).then((function (json) {
                return Promise.resolve(Curry._1(Data$Condorcet.Decode.dResultOrErrors, json));
              }));
}

var protocol = Constants$Condorcet.protocol;

var host = Constants$Condorcet.host;

exports.protocol = protocol;
exports.host = host;
exports.baseUrl = baseUrl;
exports.fetchPoll = fetchPoll;
exports.fetchResult = fetchResult;
exports.fetchManageResult = fetchManageResult;
exports.createPoll = createPoll;
exports.submitPoll = submitPoll;
exports.removeChoice = removeChoice;
/* Data-Condorcet Not a pure module */
