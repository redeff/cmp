open Pervasives
open String
open List
open Hashtbl
let bell_row = ref (1, [1])
let memo = Hashtbl.create 100 
let () = Hashtbl.add memo 0 1

(*
let rec bell n = match find_opt memo n with
  | Some k -> k
  | None -> let k = fst !bell_row in let old_list = snd !bell_row in
    if k = n - 1 then
      let new_list = fold_right (fun a bs -> (List.hd bs + a) :: bs) (snd !bell_row) [snd !bell_row |> List.hd] in
      let () = bell_row := (n, new_list) in
      bell n
    else if k = n then 
      let last = nth (snd !bell_row) (snd !bell_row |> List.length |> (+) (-1)) in
      let () = Hashtbl.add memo n last in
      Hashtbl.find memo n
    else 
      let _ = bell (n - 1) in
      bell n
;;

*)

let rec bell n = match Hashtbl.find_opt memo n with
  | Some k -> k
  | None -> let k, bell_list = !bell_row in
    if k = n then
      let () = Hashtbl.add memo n (List.hd bell_list) in
      bell n
    else if k = n - 1 then
      let new_list = fold_right (fun a bs -> (List.hd bs + a) :: bs) bell_list [List.hd bell_list] in
      let () = bell_row := (n, new_list) in
      bell n
    else
      let _ = bell (n - 1) in
      bell n



(*
let () = bell 0 |> Printf.printf "%d"
let () = bell 1 |> Printf.printf "%d"
let () = bell 2 |> Printf.printf "%d"
let () = bell 4 |> Printf.printf "%d"
*)
let () = bell 11 |> Printf.printf "%d"

(*
let rec last xs = function
  | [n] -> n
  | n :: ns -> last ns
  | [] -> raise Invalid_arument ""
*)

(*
let rec bell n = if len bell_trig > n 
  then nth n bell_trig |> head 
  else
    let () = n - 1 |> bell in
    let prev_list = (n - 1 |> get !bell_trig) in
    let new_list = fold_left (cons) [last prev_list] prev_list in
    let () = bell_trig := append new_list !bell_trig in
    bell n
*)
    
    
  

