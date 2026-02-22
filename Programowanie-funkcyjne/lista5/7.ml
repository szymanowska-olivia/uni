exception Not_productive
type 'a my_lazy = 'a state ref
and 'a state  =
| F of (unit -> 'a) 
| Value of 'a 
| Processing 

let force (f : 'a my_lazy) =
  match !f with
  | F g -> f := Processing;
           let x = try g () with e -> f := F g; raise e in
           f := Value x; x
  | Value x -> x
  | Processing -> raise Not_productive


let fix (f : 'a my_lazy -> 'a) : 'a my_lazy =
  let rec it = ref (F (fun () -> f it)) in it

let fix f = 
  let cell = ref (F f) in cell

  let fix (f : 'a my_lazy -> 'a) : 'a my_lazy =
  let rec it = ref (F (fun () -> f it)) in it