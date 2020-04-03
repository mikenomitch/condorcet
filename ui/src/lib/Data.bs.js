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
          allowComments: Json_decode.field("allow_comments", Json_decode.bool, json),
          question: Json_decode.field("question", Json_decode.string, json)
        };
}

function dResponse(json) {
  return {
          id: Json_decode.optional((function (param) {
                  return Json_decode.field("id", Json_decode.string, param);
                }), json),
          name: Json_decode.field("name", Json_decode.string, json),
          comment: Json_decode.field("comment", (function (param) {
                  return Json_decode.optional(Json_decode.string, param);
                }), json),
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

function dResultResponse(json) {
  return {
          id: Json_decode.field("id", Json_decode.string, json),
          name: Json_decode.field("name", Json_decode.string, json),
          comment: Json_decode.field("comment", (function (param) {
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
          responses: Json_decode.field("responses", (function (param) {
                  return Json_decode.list(dResultResponse, param);
                }), json),
          responseCount: Json_decode.field("response_count", Json_decode.$$int, json),
          poll: Json_decode.field("poll", dPoll, json)
        };
}

function dErrorsPollMap(json) {
  return {
          choices: Json_decode.optional((function (param) {
                  return Json_decode.field("choices", (function (param) {
                                return Json_decode.list(Json_decode.string, param);
                              }), param);
                }), json),
          question: Json_decode.optional((function (param) {
                  return Json_decode.field("question", (function (param) {
                                return Json_decode.list(Json_decode.string, param);
                              }), param);
                }), json)
        };
}

function dPollErrors(json) {
  return {
          errors: Json_decode.field("errors", dErrorsPollMap, json)
        };
}

var dPollOrErrors = Json_decode.either((function (param) {
        return Json_decode.map((function (p) {
                      return /* PollRes */Block.__(1, [p]);
                    }), dPoll, param);
      }), (function (param) {
        return Json_decode.map((function (s) {
                      return /* PollErrors */Block.__(0, [s]);
                    }), dPollErrors, param);
      }));

var dResponseOrErrors = Json_decode.either((function (param) {
        return Json_decode.map((function (r) {
                      return /* ResponseRes */Block.__(1, [r]);
                    }), dResponse, param);
      }), (function (param) {
        return Json_decode.map((function (r) {
                      return /* ResponseErrors */Block.__(0, [r]);
                    }), dPollErrors, param);
      }));

var dResultOrErrors = Json_decode.either((function (param) {
        return Json_decode.map((function (r) {
                      return /* ResultRes */Block.__(1, [r]);
                    }), dResult, param);
      }), (function (param) {
        return Json_decode.map((function (r) {
                      return /* ResultErrors */Block.__(0, [r]);
                    }), dPollErrors, param);
      }));

var Decode = {
  dPoll: dPoll,
  dResponse: dResponse,
  dfullResults: dfullResults,
  dWinnerMap: dWinnerMap,
  dResultResponse: dResultResponse,
  dResult: dResult,
  dErrorsPollMap: dErrorsPollMap,
  dPollErrors: dPollErrors,
  dPollOrErrors: dPollOrErrors,
  dResponseOrErrors: dResponseOrErrors,
  dResultOrErrors: dResultOrErrors
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
                /* :: */[
                  /* tuple */[
                    "allow_comments",
                    poll.allowComments
                  ],
                  /* [] */0
                ]
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
                  "comment",
                  Json_encode.nullable((function (prim) {
                          return prim;
                        }), response.comment)
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
              ]
            ]);
}

function encodeChoice(choice) {
  return Json_encode.object_(/* :: */[
              /* tuple */[
                "choice",
                choice
              ],
              /* [] */0
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
exports.encodeChoice = encodeChoice;
exports.encodePollPost = encodePollPost;
exports.encodeResponsePost = encodeResponsePost;
/* dPollOrErrors Not a pure module */
