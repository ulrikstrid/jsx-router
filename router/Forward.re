let make = (~path: string, children) => {
  let (path_list, _typ) = Dispatch.of_dsl(path);

  `Multi(
    Base.List.map(
      children,
      ~f=
        fun
        | `Single(r) => [r]
        | `Multi(r) => r,
    )
    |> Base.List.concat
    |> Base.List.map(~f=((p, typ, handler)) =>
         (Base.List.concat([path_list, p]), typ, handler)
       ),
  );
};

let createElement = (~path: string, ~children, ()) => make(~path, children);
