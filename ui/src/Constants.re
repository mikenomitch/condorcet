type envType = {
  protocol: string,
  host: string,
  indexType: string,
};

let currentEnv: envType = [%raw {| window.env |}];
let protocol = currentEnv.protocol;
let host = currentEnv.host;
let indexType = currentEnv.indexType;