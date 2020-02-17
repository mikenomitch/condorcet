// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var Dnd = require("re-dnd/src/Dnd.bs.js");
var List = require("bs-platform/lib/js/list.js");
var $$Array = require("bs-platform/lib/js/array.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var Caml_obj = require("bs-platform/lib/js/caml_obj.js");
var ArrayExt$Condorcet = require("./lib/ArrayExt.bs.js");

var eq = Caml_obj.caml_equal;

var Item = {
  eq: eq
};

var Container = Dnd.MakeSingletonContainer({ });

var Items = Dnd.Make(Item, Container);

function reducer(state, action) {
  var match = action[0];
  if (match !== undefined) {
    var match$1 = match;
    if (match$1.tag) {
      return state;
    } else {
      var placement = match$1[1];
      return ArrayExt$Condorcet.reinsert(state, match$1[0], placement ? /* `Before */[
                    -825833313,
                    placement[0]
                  ] : /* Last */847656566);
    }
  } else {
    return state;
  }
}

var initialState = [
  1,
  2,
  3,
  4,
  5,
  6,
  7
];

function TakePollChoices(Props) {
  var match = React.useReducer(reducer, initialState);
  var dispatch = match[1];
  var state_as_list = $$Array.to_list(match[0]);
  return React.createElement(Items.DndManager.make, {
              onReorder: (function (result) {
                  return Curry._1(dispatch, /* ReorderItems */[result]);
                }),
              children: React.createElement(Items.DroppableContainer.make, {
                    id: /* () */0,
                    axis: /* Y */1,
                    children: $$Array.of_list(List.mapi((function (index, item) {
                                return React.createElement(Items.DraggableItem.make, {
                                            id: item,
                                            containerId: /* () */0,
                                            index: index,
                                            children: /* `Children */[
                                              -904145569,
                                              String(item)
                                            ],
                                            key: String(item)
                                          });
                              }), state_as_list))
                  })
            });
}

var make = TakePollChoices;

exports.Item = Item;
exports.Container = Container;
exports.Items = Items;
exports.reducer = reducer;
exports.initialState = initialState;
exports.make = make;
/* Container Not a pure module */