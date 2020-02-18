// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var Block = require("bs-platform/lib/js/block.js");
var Json_decode = require("@glennsl/bs-json/src/Json_decode.bs.js");
var Json_encode = require("@glennsl/bs-json/src/Json_encode.bs.js");

function dPoll(json) {
  return {
          id: Json_decode.optional((function (param) {
                  return Json_decode.field("id", Json_decode.string, param);
                }), json),
          choices: Json_decode.field("choices", (function (param) {
                  return Json_decode.list(Json_decode.string, param);
                }), json),
          manageToken: Json_decode.optional((function (param) {
                  return Json_decode.field("manage_token", Json_decode.string, param);
                }), json),
          question: Json_decode.field("question", Json_decode.string, json)
        };
}

function dResponse(json) {
  return {
          id: Json_decode.optional((function (param) {
                  return Json_decode.field("id", Json_decode.$$int, param);
                }), json),
          name: Json_decode.field("name", Json_decode.string, json),
          order: Json_decode.field("order", (function (param) {
                  return Json_decode.list(Json_decode.string, param);
                }), json)
        };
}

function dfullResults(json) {
  return {
          borda: Json_decode.field("borda", (function (param) {
                  return Json_decode.dict(Json_decode.$$int, param);
                }), json),
          plurality: Json_decode.field("plurality", (function (param) {
                  return Json_decode.dict(Json_decode.$$int, param);
                }), json),
          ranked: Json_decode.field("ranked", (function (param) {
                  return Json_decode.list((function (param) {
                                return Json_decode.list(Json_decode.string, param);
                              }), param);
                }), json)
        };
}

function dWinnerMap(json) {
  return {
          borda: Json_decode.field("borda", (function (param) {
                  return Json_decode.list(Json_decode.string, param);
                }), json),
          ranked: Json_decode.field("ranked", (function (param) {
                  return Json_decode.list(Json_decode.string, param);
                }), json),
          plurality: Json_decode.field("plurality", (function (param) {
                  return Json_decode.list(Json_decode.string, param);
                }), json),
          condorcet: Json_decode.field("condorcet", (function (param) {
                  return Json_decode.optional(Json_decode.string, param);
                }), json)
        };
}

function dResult(json) {
  return {
          winners: Json_decode.optional((function (param) {
                  return Json_decode.field("winners", dWinnerMap, param);
                }), json),
          fullResults: Json_decode.optional((function (param) {
                  return Json_decode.field("full_results", dfullResults, param);
                }), json),
          names: Json_decode.field("names", (function (param) {
                  return Json_decode.list(Json_decode.string, param);
                }), json),
          responseCount: Json_decode.field("response_count", Json_decode.$$int, json),
          poll: Json_decode.field("poll", dPoll, json)
        };
}

function dErrorsMap(json) {
  return {
          choices: Json_decode.optional((function (param) {
                  return Json_decode.field("choices", (function (param) {
                                return Json_decode.list(Json_decode.string, param);
                              }), param);
                }), json),
          question: Json_decode.optional((function (param) {
                  return Json_decode.field("questions", (function (param) {
                                return Json_decode.list(Json_decode.string, param);
                              }), param);
                }), json)
        };
}

function dErrors(json) {
  return {
          errors: Json_decode.field("errors", dErrorsMap, json)
        };
}

var dPollOrErrors = Json_decode.either((function (param) {
        return Json_decode.map((function (p) {
                      return /* Poll */Block.__(1, [p]);
                    }), dPoll, param);
      }), (function (param) {
        return Json_decode.map((function (s) {
                      return /* Errors */Block.__(0, [s]);
                    }), dErrors, param);
      }));

var Decode = {
  dPoll: dPoll,
  dResponse: dResponse,
  dfullResults: dfullResults,
  dWinnerMap: dWinnerMap,
  dResult: dResult,
  dErrorsMap: dErrorsMap,
  dErrors: dErrors,
  dPollOrErrors: dPollOrErrors
};

function encodePoll(poll) {
  return Json_encode.object_(/* :: */[
              /* tuple */[
                "question",
                poll.question
              ],
              /* :: */[
                /* tuple */[
                  "choices",
                  Json_encode.list((function (prim) {
                          return prim;
                        }), poll.choices)
                ],
                /* [] */0
              ]
            ]);
}

function encodeResponse(response) {
  return Json_encode.object_(/* :: */[
              /* tuple */[
                "name",
                response.name
              ],
              /* :: */[
                /* tuple */[
                  "order",
                  Json_encode.list((function (prim) {
                          return prim;
                        }), response.order)
                ],
                /* [] */0
              ]
            ]);
}

function encodePollPost(poll) {
  return Json_encode.object_(/* :: */[
              /* tuple */[
                "poll",
                encodePoll(poll)
              ],
              /* [] */0
            ]);
}

function encodeResponsePost(poll) {
  return Json_encode.object_(/* :: */[
              /* tuple */[
                "response",
                encodeResponse(poll)
              ],
              /* [] */0
            ]);
}

exports.Decode = Decode;
exports.encodePoll = encodePoll;
exports.encodeResponse = encodeResponse;
exports.encodePollPost = encodePollPost;
exports.encodeResponsePost = encodeResponsePost;
/* dPollOrErrors Not a pure module */
