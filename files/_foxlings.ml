open Scanf
open Printf

let rec distribute num right stuff visited=
 if visited.(num).(right)= -1 then
  visited.(num).(right)<-(
 match right with
 |0->
  if fst stuff.(0)<=num && snd stuff.(0)>=num
   then 1
   else 0
 |_->
  let rr=ref 0 in
  for e=(fst stuff.(right)) to (snd stuff.(right)) do
   if num-e>=0 then rr:= !rr+
    (distribute (num-e) (right-1) stuff visited)
  done;
  !rr
  );
 visited.(num).(right)

let oneCase()=
 scanf "%i %i\n" (fun foxen items->
  let stuff=Array.init foxen (fun e->
   scanf "%i %i\n" (fun a b->(a,b)) ) in
  let vv=Array.init (items+1) (fun e->Array.make foxen (-1)) in
  printf "%i\n" (distribute items (foxen-1) stuff vv)
 )

let cases=scanf "%i\n" (fun e->e);;
for e=1 to cases do oneCase() done;;