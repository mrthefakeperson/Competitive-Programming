open System.IO
let inp=StreamReader(System.Console.OpenStandardInput())
let first=fun e->match e with|(a,_,_)->a
let second=fun e->match e with|(_,b,_)->b
let third=fun e->match e with|(_,_,c)->c
let rec merge l1 l2=
 match (l1,l2) with
 |([],ll)|(ll,[])->ll
 |((hd1:int*int*int)::tl1,(hd2:int*int*int)::tl2)->
  if second hd1=second hd2 then
   if third hd1+third hd2=0
    then merge tl1 tl2
    else (System.Math.Max(first hd1,first hd2),second hd1,third hd1+third hd2)::merge tl1 tl2
  elif second hd1>second hd2 then hd2::merge l1 tl2
  else hd1::merge tl1 l2
let n,desired=inp.ReadLine()|>int,inp.ReadLine()|>int
let xPositions=ref []
for e in 1..n do
 match inp.ReadLine().Split(' ')|>Array.map int with
 |[|a;b;c;d;e|]->
  xPositions:=(a,b,e)::(a,d,-e)::(c,b,-e)::(c,d,e):: !xPositions
xPositions:=List.sortBy first !xPositions
let _=
 List.fold (fun (acc:(int*int*int) list list*(int*int*int) list*int) (e:int*int*int)->
  let totalList,thisXList,thisX=acc
  if first e<>thisX
   then (thisXList::totalList,[e],first e)
   else (totalList,e::thisXList,thisX)
 ) ([],[],0) !xPositions|>(fun e->List.rev (second e::first e))
  |>List.map (fun e->
   List.sortBy second e)|>List.filter ((<>)[])
    |>List.fold (fun (columnWTotal:(int*int*int) list*int64*int) (e:(int*int*int) list)->
       let column,total,lastX=columnWTotal
       let newColumn= //merge e (sorted list of coords) with column (equal y coordinates must be combined)
        merge e column
       let mxx=e.[0]
       let traverseColumn=
        if column=[]
         then 0L
         else
          List.fold (fun (acc:int64*int*int) e->
           let thisTotal,currentTint,lastChange=acc
           if currentTint>=desired
            then (thisTotal+int64(second e-lastChange),currentTint+third e,second e)
            else (thisTotal,currentTint+third e,second e)
          ) (0L,0,0) column|>first
       (newColumn,traverseColumn*(int64(first mxx-lastX))+total,first mxx)         
      ) ([],0L,0)|>second
       |>System.Console.WriteLine




System.Console.ReadLine()