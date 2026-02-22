 type 'a ltree = 'a node lazy_t
 and ' a node = 
  | Leaf
  | Node of 'a ltree * 'a * 'a ltree

let rec build_tree l r = lazy (
    let v = (fst l + fst r, snd l + snd r) in
    Node (build_tree l v, v, build_tree v r))

let rationals : (int * int) ltree = build_tree (0, 1) (1, 0)