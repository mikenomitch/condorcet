let header =
  ReactDOMRe.Style.make(
    ~backgroundColor="#eee",
    ~fontSize="20px",
    ~width="100%",
    (),
  );
let background = ReactDOMRe.Style.make(~backgroundColor="green", ());
let test = ReactDOMRe.Style.combine(header, background);