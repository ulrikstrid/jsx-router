type route('a) = [
  | `Single(Dispatch.route('a))
  | `Multi(list(Dispatch.route('a)))
];

type router('a) = {
  routes: list(Dispatch.route('a)),
  route_list: list(string),
  match: string => result('a, string),
};

let make: list(route('a)) => router('a);

let createElement: (~children: list(route('a)), unit) => router('a);

module Route: {
  type handler('a) = (~params: list((string, string))) => 'a;

  let make: (~path: string, handler('a)) => route('a);

  let createElement:
    (~path: string, ~handler: handler('a), ~children: list(unit), unit) =>
    route('a);
};

module Forward: {
  let make: (~path: string, list(route('a))) => route('a);

  let createElement:
    (~path: string, ~children: list(route('a)), unit) => route('a);
};
