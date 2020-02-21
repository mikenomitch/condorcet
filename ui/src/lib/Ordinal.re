[@react.component]
let make = (~num: int) => {
  switch (num) {
  | 0 => R.s("0th")
  | 1 => R.s("1st")
  | 2 => R.s("2nd")
  | 3 => R.s("3rd")
  | other => R.s(string_of_int(other) ++ "th")
  };
};