[@react.component]
let make = (~link) => {
  // let copyLink = _ => {
  //   Js.log(link);
  // };
  <div className="copyable-link">
    {R.s(link)}
  </div>;
};