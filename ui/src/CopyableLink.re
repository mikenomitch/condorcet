[@react.component]
let make = (~link) => {
  let copyLink = _ => {
    Js.log(link);
  };

  <div onClick=copyLink className="copyable-link"> {R.s(link)} </div>;
};