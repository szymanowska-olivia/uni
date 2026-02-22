 type 'a ltree = 'a node lazy_t
 and ' a node = 
  | Leaf
  | Node of 'a ltree * 'a * 'a ltree

let rec build_tree l r = lazy (
    let v = (fst l + fst r, snd l + snd r) in
    Node (build_tree l v, v, build_tree v r))

let rationals : (int * int) ltree = build_tree (0, 1) (1, 0)

let rec bfs tree =
  match Lazy.force tree with
  | Leaf -> Seq.empty
  | Node (l, v, r) -> fun () -> Seq.Cons (v, (Seq.interleave (bfs l) (bfs r)))


let stream_of_rationals () : (int * int) Seq.t = bfs rationals

