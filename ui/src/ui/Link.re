[@react.component]
let make = (~linkTo, ~className="", ~children) => {
  let onClick = evt => {
    ReactEvent.Synthetic.preventDefault(evt);
    ReasonReactRouter.push(linkTo);
  };

  <a className onClick href=linkTo> children </a>;
};