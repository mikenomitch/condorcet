[@react.component]
let make = () => {
  <div className="page">
    <h2> {R.s("Response successfully submitted.")} </h2>
    <Link className="centered" linkTo="/"> {R.s("Go to Homepage")} </Link>
  </div>;
};