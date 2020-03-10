// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var List = require("bs-platform/lib/js/list.js");
var $$Array = require("bs-platform/lib/js/array.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var R$Condorcet = require("./lib/R.bs.js");
var Api$Condorcet = require("./lib/Api.bs.js");
var ReasonReactRouter = require("reason-react/src/ReasonReactRouter.js");

function EditResults(Props) {
  var notify = Props.notify;
  var result = Props.result;
  var match = React.useState((function () {
          return ;
        }));
  var setChoiceToRemove = match[1];
  var choiceToRemove = match[0];
  var match$1 = React.useState((function () {
          return ;
        }));
  var setResponseToRemove = match$1[1];
  var responseToRemove = match$1[0];
  var renderResponse = function (response) {
    return React.createElement("div", {
                key: response.name,
                className: "remove-choice"
              }, React.createElement("div", undefined, React.createElement("button", {
                        className: "button button-sm",
                        onClick: (function (param) {
                            return Curry._1(setResponseToRemove, (function (_state) {
                                          return response;
                                        }));
                          })
                      }, React.createElement("i", {
                            className: "far fa-trash-alt"
                          }))), React.createElement("div", undefined, R$Condorcet.s(response.name)));
  };
  var renderChoice = function (choice) {
    return React.createElement("div", {
                key: choice,
                className: "remove-choice"
              }, React.createElement("div", undefined, React.createElement("button", {
                        className: "button button-sm",
                        onClick: (function (param) {
                            return Curry._1(setChoiceToRemove, (function (_state) {
                                          return choice;
                                        }));
                          })
                      }, React.createElement("i", {
                            className: "far fa-trash-alt"
                          }))), React.createElement("div", undefined, R$Condorcet.s(choice)));
  };
  var renderChoiceRemove = function (poll) {
    var showRemove = List.length(poll.choices) > 2;
    var match = poll.id;
    var match$1 = poll.manageToken;
    if (showRemove && match !== undefined && match$1 !== undefined) {
      return React.createElement("div", undefined, React.createElement("h4", {
                      className: "centered"
                    }, R$Condorcet.s("Select a choice to remove:")), React.createElement("div", {
                      className: "remove-choice-list"
                    }, $$Array.of_list(List.map(renderChoice, poll.choices))));
    } else {
      return null;
    }
  };
  var renderResponseRemove = function (result) {
    var showRemove = List.length(result.responses) > 0;
    if (showRemove) {
      return React.createElement("div", undefined, React.createElement("h4", {
                      className: "centered"
                    }, R$Condorcet.s("Select a response to remove:")), React.createElement("div", {
                      className: "remove-choice-list"
                    }, $$Array.of_list(List.map(renderResponse, result.responses))));
    } else {
      return null;
    }
  };
  var renderChoiceRemovalConfirmation = function (poll, choice) {
    var match = poll.manageToken;
    if (match !== undefined) {
      var token = match;
      return React.createElement("div", undefined, React.createElement("h4", {
                      className: "centered"
                    }, R$Condorcet.s("Are you sure?")), React.createElement("p", undefined, R$Condorcet.s("'" + (choice + "' will be permanently removed and the results will be recalculated"))), React.createElement("div", {
                      className: "centered"
                    }, React.createElement("button", {
                          className: "button m-h-sm",
                          onClick: (function (param) {
                              return Curry._1(setChoiceToRemove, (function (_state) {
                                            return ;
                                          }));
                            })
                        }, R$Condorcet.s("Keep Choice")), React.createElement("button", {
                          className: "button m-h-sm",
                          onClick: (function (param) {
                              var manageToken = token;
                              var choice$1 = choice;
                              Api$Condorcet.removeChoice(manageToken, choice$1).then((function (resultVariant) {
                                      if (resultVariant.tag) {
                                        ReasonReactRouter.push("/manage-poll/" + manageToken);
                                        Curry._2(notify, "info", "Results recalculated without choice");
                                        return Promise.resolve(/* () */0);
                                      } else {
                                        Curry._2(notify, "error", "There was an issue removing the choice");
                                        return Promise.resolve(/* () */0);
                                      }
                                    }));
                              return /* () */0;
                            })
                        }, R$Condorcet.s("Remove Choice"))));
    } else {
      return null;
    }
  };
  var renderResponseRemovalConfitmation = function (poll, response) {
    var match = poll.manageToken;
    if (match !== undefined) {
      var token = match;
      return React.createElement("div", undefined, React.createElement("h4", {
                      className: "centered"
                    }, R$Condorcet.s("Are you sure?")), React.createElement("p", undefined, R$Condorcet.s("'" + (response.name + "' will be permanently removed and the results will be recalculated"))), React.createElement("div", {
                      className: "centered"
                    }, React.createElement("button", {
                          className: "button m-h-sm",
                          onClick: (function (param) {
                              return Curry._1(setResponseToRemove, (function (_state) {
                                            return ;
                                          }));
                            })
                        }, R$Condorcet.s("Keep Response")), React.createElement("button", {
                          className: "button m-h-sm",
                          onClick: (function (param) {
                              var manageToken = token;
                              var id = response.id;
                              Api$Condorcet.destroyResponse(manageToken, id).then((function (res) {
                                      var match = res.status;
                                      if (match >= 202) {
                                        if (match !== 204) {
                                          Curry._2(notify, "error", "There was an error removing this response");
                                          return Promise.resolve(/* () */0);
                                        }
                                        
                                      } else if (match < 200) {
                                        Curry._2(notify, "error", "There was an error removing this response");
                                        return Promise.resolve(/* () */0);
                                      }
                                      ReasonReactRouter.push("/manage-poll/" + manageToken);
                                      Curry._2(notify, "info", "Results recalculated without response");
                                      return Promise.resolve(/* () */0);
                                    }));
                              return /* () */0;
                            })
                        }, R$Condorcet.s("Remove Response"))));
    } else {
      return null;
    }
  };
  var renderBackBtn = function (manageToken) {
    if (manageToken !== undefined) {
      var manageToken$1 = manageToken;
      return React.createElement("div", {
                  className: "centered m-t-md"
                }, React.createElement("button", {
                      className: "button",
                      onClick: (function (param) {
                          return ReasonReactRouter.push("/manage-poll/" + manageToken$1);
                        })
                    }, R$Condorcet.s("Back")));
    } else {
      return null;
    }
  };
  return React.createElement("div", {
              className: "page"
            }, React.createElement("h3", {
                  className: "centered"
                }, R$Condorcet.s("Edit Results")), choiceToRemove !== undefined ? renderChoiceRemovalConfirmation(result.poll, choiceToRemove) : (
                responseToRemove !== undefined ? renderResponseRemovalConfitmation(result.poll, responseToRemove) : React.createElement("div", undefined, renderChoiceRemove(result.poll), renderResponseRemove(result), renderBackBtn(result.poll.manageToken))
              ));
}

var make = EditResults;

exports.make = make;
/* react Not a pure module */
