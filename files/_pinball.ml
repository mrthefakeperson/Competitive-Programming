
let qqq=int_of_string(input_line stdin)
let flQ=float_of_int qqq
let scores=Array.init qqq (fun e->int_of_string(input_line stdin))
let total=ref 0.
let rec merge ll1 ll2 lenThing=
 match (ll1,ll2) with
 |([],ll)|(ll,[])->ll
 |(hd1::tl1,hd2::tl2)->
  (
  match hd1 with
  |hh when hh>hd2->hd1::(merge tl1 ll2 (lenThing-1))
  |hh->
   total:= !total+.(float_of_int(lenThing)/.flQ);
   hd2::(merge ll1 tl2 lenThing)
  )
let rec mergeSort atLeft jump=
 match jump with
 |1->[scores.(atLeft)]
 |2->
  (
  match (scores.(atLeft),scores.(atLeft+1)) with
  |(sc,sc2) when sc>sc2->[sc;sc2]
  |(sc,sc2)->
   total:= !total+.(1./.flQ);
   [sc2;sc]
  )
 |_->
  let nNj=jump/2 in
  if jump mod 2=1 then merge (mergeSort atLeft nNj) (mergeSort (atLeft+nNj) (nNj+1)) (nNj)
  else merge(mergeSort atLeft nNj) (mergeSort (atLeft+nNj) nNj) (nNj);;
mergeSort 0 qqq;;


let outt=Printf.sprintf "%0.*f" 2 (((flQ+.1.)/.2.)-. !total);;
(*let outt=string_of_float(float_of_string(outtt)+.0.01);;*)
print_string outt;;
