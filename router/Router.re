type route('a) = [
  | `Single(Dispatch.route('a))
  | `Multi(list(Dispatch.route('a)))
];

type router('a) = {
  routes: list(Dispatch.route('a)),
  route_list: list(string),
  match: string => result('a, string),
};

let make = children => {
  let routes =
    Base.List.map(
      children,
      ~f=
        fun
        | `Single(r) => [r]
        | `Multi(r) => r,
    )
    |> Base.List.concat;

  let route_list =
    Base.List.map(routes, ~f=((a, b, _)) => "/" ++ Dispatch.to_dsl((a, b)))
    |> Base.List.sort(~compare=Base.String.compare);

  let match = Dispatch.dispatch(routes);

  {routes, route_list, match};
};

let createElement = (~children, ()) => make(children);

module Route = Route;
module Forward = Forward;
