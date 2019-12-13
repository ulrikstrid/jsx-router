open TestFramework;
open Router;

let jsxRouter =
  <Router>
    <Route path="/test" handler={(~params as _) => "/test"} />
    <Forward path="/api">
      <Route path="/user" handler={(~params as _) => "/api/user"} />
      <Route
        path="/user/:user_id"
        handler={(~params) => {
          switch (params) {
          | [("user_id", user_id)] => "/api/user/" ++ user_id
          | _ => "no user_id, should not happen"
          }
        }}
      />
    </Forward>
    <Forward path="/test">
      <Route path="/test" handler={(~params as _) => "/test/test"} />
      <Forward path="test2">
        <Route
          path="/test3"
          handler={(~params as _) => "/test/test2/test3"}
        />
      </Forward>
    </Forward>
  </Router>;

describe("Routing table", ({test}) => {
  test("Can get a routing table", ({expect}) => {
    expect.lines(jsxRouter.route_list).toEqualLines([
      "/api/user",
      "/api/user/:user_id",
      "/test",
      "/test/test",
      "/test/test2/test3",
    ])
  })
});

describe("Basic routing", ({test}) => {
  test("Can match a bascic route", ({expect}) => {
    expect.result(jsxRouter.match("/test")).toBe(
      ~equalsOk=(==),
      Ok("/test"),
    )
  });

  test("Can nest routes", ({expect}) => {
    expect.result(jsxRouter.match("/test/test")).toBe(
      ~equalsOk=(==),
      Ok("/test/test"),
    )
  });

  test("Can deeply nest routes", ({expect}) => {
    expect.result(jsxRouter.match("/test/test2/test3")).toBe(
      ~equalsOk=(==),
      Ok("/test/test2/test3"),
    )
  });

  test("Can forward params", ({expect}) => {
    expect.result(jsxRouter.match("/api/user/123")).toBe(
      ~equalsOk=(==),
      Ok("/api/user/123"),
    )
  });

  test("Can fail to match", ({expect}) => {
    expect.result(jsxRouter.match("/test/user/123")).toBe(
      ~equalsError=(==),
      Error("no matching routes found"),
    );
    expect.result(jsxRouter.match("/api/user/123/123")).toBe(
      ~equalsError=(==),
      Error("no matching routes found"),
    );
  });
});
