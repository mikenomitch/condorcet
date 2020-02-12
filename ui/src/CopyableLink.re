[@react.component]
let make = (~link: string) => {
  let ignoreMe = () => Js.log("some string");

  <CopyToClipboard text=link onCopy=ignoreMe>
    <div className="copyable-link"> {R.s(link)} </div>
  </CopyToClipboard>;
};