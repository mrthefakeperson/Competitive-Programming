(*merge sort*)
type item=    (*both have position as fst, which is used to sort*)
|Data of int (*height*)
|Request of int (*which query?*)
let qq=read_int()
let stuff=Array.make 20001 [];;
Scanf.scanf "%i" (fun e->
 stuff.(e)<-(0,Data(e))::stuff.(e)     (*position is where it is found in the line of trees*)
);;
for e=1 to (qq-1) do
 Scanf.scanf " %i" (fun ee->stuff.(ee)<-(e,Data(ee))::stuff.(ee))
done;;
let qqq=Scanf.scanf "\n%i\n" (fun e->e);;
for e=0 to (qqq-1) do
 Scanf.scanf "%i %i %i\n" (fun left right height->
  stuff.(height)<-(right,Request(-e-1))::(left-1,Request(e))::stuff.(height)
 )
done;;
let ans=Array.make qqq 0
let items=ref (List.map (fun e->
 ([e],(match snd e with |Data(x)->x |_->0))    (*sublist,sum of everything inside heightwise*)
) (Array.fold_left (fun acc e->(List.rev e)@acc) [] stuff));;
let comparison a b toAdd=
 if fst a<=fst b
  then true
  else((     (*b must merge left, ahead of a*)
   match b with
   |(_,Request(place))->
    if place<0
	 then ans.(-(place+1))<-ans.(-(place+1))-toAdd
	 else ans.(place)<-ans.(place)+toAdd
   |_->()
  );false)
let rec merge aList bList aListSum=
 match (aList,bList) with
 |(hda::tla,hdb::tlb)->
  if comparison hda hdb aListSum
   then
    match snd hda with
	|Data(x)->hda::(merge tla bList (aListSum-x))
	|_->hda::(merge tla bList aListSum)
   else(
    hdb::(merge aList tlb aListSum) )
 |([],ll)|(ll,[])->ll
 (*
let rec mergeSort depth=
 match !items with
 |[]->([],0)
 |hd::tl when depth=0->
  items:=tl;
  hd
 |_->
  let ff,ss=(mergeSort (depth-1)),(mergeSort (depth-1)) in
  (merge (fst ff) (fst ss) (snd ff),snd ff+snd ss);;
  *)
 
let rec doubleFoldAction=function
|(l1,s1)::(l2,s2)::(l3,s3)::(l4,s4)::(l5,s5)::(l6,s6)::(l7,s7)::(l8,s8)::tl->
 (merge(merge(merge(l1)(l2)(s1))
       (merge(l3)(l4)(s3))(s1+s2))
	         (merge(merge(l5)(l6)(s5))(merge(l7)(l8)(s7))(s5+s6))(s1+s2+s3+s4),s1+s2+s3+s4+s5+s6+s7+s8)
			 ::
			   doubleFoldAction tl
|(leftList,lsum)::(rightList,rsum)::tl->
 (merge leftList rightList lsum,lsum+rsum)::doubleFoldAction tl
|[q]->[q]
|[]->[]
let rec mergeSort=function
|[_]->()
|ll->
 mergeSort (doubleFoldAction ll);;
 
mergeSort !items;;
Array.iter (fun e->Printf.printf "%i\n" e) ans