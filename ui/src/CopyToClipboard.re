[@bs.module "./imports/copyToClipboard"] [@react.component]
external make:
  (~text: string, ~onCopy: unit => unit, ~children: React.element) =>
  React.element =
  "default";