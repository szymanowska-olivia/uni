let perm_type : ty_def = (
  "Perm",
  [
    Ctor ("perm_nil", []);
    Ctor ("perm_cons", ["A"; "list"; "list"; "Perm"]);
    Ctor ("perm_swap", ["A"; "A"; "list"]);
    Ctor ("perm_trans", ["list"; "list"; "list"; "Perm"; "Perm"])
  ]
)
