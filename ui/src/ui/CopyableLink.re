[@bs.val] external setTimeout: (unit => unit, int) => float = "setTimeout";

[@react.component]
let make = (~link: string) => {
  let (isCopied, setCopied) = React.useState(() => false);

  let ignoreMe = () => {
    setCopied(_state => true);
    setTimeout(() => {setCopied(_state => false)}, 3000) |> ignore;
  };

  <CopyToClipboard text=link onCopy=ignoreMe>
    <div>
      <div className="copyable-link"> {R.s(link)} </div>
      {isCopied
         ? <span className="copied"> {R.s("Copied to clipboard!")} </span>
         : React.null}
    </div>
  </CopyToClipboard>;
};