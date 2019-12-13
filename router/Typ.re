type route('a) = [
  | `Single(Dispatch.route('a))
  | `Multi(list(Dispatch.route('a)))
];

type router('a) = {
  routes: list(Dispatch.route('a)),
  route_list: list(string),
  match: string => result('a, string),
};
