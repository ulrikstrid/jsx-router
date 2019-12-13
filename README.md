# router

A router based on [ocaml-dispatch](https://github.com/inhabitedtype/ocaml-dispatch) with a easy to use JSX based API.

## TODO:

- [ ] Handle routing on method
- [ ] Support adding middlewares
- [ ] Minimize dependencies (we don't really need base)
- [ ] Explore alternatives for underlying router implementation

## Example:

```ocaml
let jsxRouter =
  <App>
    <Route
      path="/test"
      handler={(~params as _) => print_endline("hit the route /test")}
    />
    <Forward path="/api">
      <Route
        path="/user"
        handler={(~params as _) => {
          print_endline("hit the route /api/user");
          print_endline("all users");
        }}
      />
      <Route
        path="/user/:user_id"
        handler={(~params) => {
          Base.List.Assoc.find(params, ~equal=(a, b) => a == b, "user_id")
          |> (
            fun
            | Some(value) =>
              {print_endline("hit the route /api/user/:user_id");
               print_endline("user with id: " ++ value)}
            | None => print_endline("no user_id, should not happen")
          )
        }}
      />
    </Forward>
    <Forward path="/test">
      <Route
        path="/test"
        handler={(~params as _) => print_endline("hit the route /test/test")}
      />
      <Forward path="test2">
        <Route
          path="/test3"
          handler={(~params as _) =>
            print_endline("hit the route /test/test2/test3")
          }
        />
      </Forward>
    </Forward>
  </App>;
```

### List routes

```ocaml
Base.List.iter(~f=print_endline, jsxRouter.route_list);

-------------------------------------------------------

api/user
api/user/:user_id
test
test/test2/test
test/test2/test3
```

### Matching routes

```ocaml
jsxRouter.match("/api/user");
// hit the route /api/user
// all users

jsxRouter.match("/api/user/1");
// hit the route /api/user/:user_id
// user with id: 1

jsxRouter.match("/test");
// hit the route /test

jsxRouter.match("/test/test2/test3");
// hit the route /test/test2/test3

jsxRouter.match("/test/test");
// hit the route /test/test

jsxRouter.match("/user/1") |> Base.Result.iter_error(~f=print_endline);
// no matching routes found
```
