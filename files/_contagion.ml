open Scanf
open Printf
let (++) a b=Int64.add a b
let (--) a b=Int64.sub a b
let ( ** ) a b=Int64.mul a b
let cast=Int64.of_int;;

let n=scanf "%i\n" (fun e->e)
let cities=Array.init n (fun e->scanf "%i %i\n" (fun a b->(cast a,cast b)))
let start=scanf "%i\n" (fun e->e-1)
let q=scanf "%i" (fun e->e)
let queries=Array.init q (fun ee->scanf "\n%Ld" (fun e->e));;

let dist (a,b) (c,d)=(c--a)**(c--a)++(b--d)**(b--d);;
let vv=Array.init n (fun e-> -1L);;
vv.(start)<-0L;;
(*djikstra's algorithm*)
let rec path node toVisit=
 match toVisit with
 |[]->()
 |_->
  let ll=ref [] in
  let accMin,acc=ref (cast(-1)),ref(-1) in
  List.iter (fun place->
    let newPath=vv.(node)++(dist cities.(node) cities.(place)) in
	if vv.(place)= -1L || vv.(place)>newPath then(
	 vv.(place)<-newPath
	);
	if !accMin= -1L || vv.(place)< !accMin
	 then
	  (ll:=place:: !ll;accMin:=vv.(place);acc:=place)
	 else
	  (ll:=place:: !ll)
  ) (List.filter ((<>) node) toVisit);
  path !acc !ll;;
let rec range=function
|0->[]
|n->(n-1)::(range (n-1));;
path start (range n);;
Array.sort (fun a b->match () with () when a<b-> -1|() when a=b->0|() when a>b->1) vv;;

let rec find x ll=
 let good place thing=
  if place>Array.length ll then false else thing>=ll.(place-1)
  in
 let jump,place=ref (Array.length ll),ref 0 in
 while !jump>0 do
  if good (!place+ !jump) x then
   place:= !place+ !jump;
  jump:= !jump/2
 done;
 while good (!place+1) x do place:= !place +1 done;
 !place;;
 
Array.iter (fun e->
 find e vv |> printf "%i\n"
) queries;;
(*
Array.iter (printf "%i  ") vv;;
printf "\n";;
*)