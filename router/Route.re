type handler('a) = (~params: list((string, string))) => 'a;

let make = (~path, handler) =>
  `Single(
    Dispatch.of_dsl(path)
    |> (((a, b)) => (a, b, (params, _rest) => handler(~params))),
  );

let createElement = (~path, ~handler: handler('a), ~children as _, ()) => {
  make(~path, handler);
};
