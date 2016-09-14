open System.IO
let inp=StreamReader(System.Console.OpenStandardInput())
let qq=inp.ReadLine()|>int
let lookup,cost,edges=Array2D.init 1001 1001 (fun _ _->(0,0)),Array2D.init 1001 1001 (fun _ _->0),ref []
for penID in 1..qq do
 let input=Array.map int (inp.ReadLine().Split(' '))
 for e_ in 1..input.[0] do
  let aa,bb=if e_=input.[0] then (input.[1],input.[input.[0]]) else (input.[e_],input.[e_+1])
  let a,b=System.Math.Min(aa,bb),System.Math.Max(aa,bb)
  let costt=input.[e_+input.[0]]
  cost.[a,b]<-costt
  if lookup.[a,b]=(0,0)
   then lookup.[a,b]<-(penID,0)
   else lookup.[a,b]<-(fst lookup.[a,b],penID)
Array2D.iteri (fun x y e->if e<>(0,0) then edges:=(e,cost.[x,y]):: !edges) lookup
edges:=List.sortBy snd !edges
let lowestAccess=Array.init (qq+1) (fun e->e)
let rec unravel e=
 if lowestAccess.[e]=e
  then e
  else
   lowestAccess.[e]<-unravel lowestAccess.[e]
   lowestAccess.[e]
let L=List.init (qq) (fun e->e+1)
let rec breakWall=function
|hd::tl->
 let ((a,b),cost)=hd
 //printfn "%A,%A" hd lowestAccess
 if unravel a<>unravel b
  then
   if lowestAccess.[a]>lowestAccess.[b]
    then lowestAccess.[lowestAccess.[a]]<-lowestAccess.[b]
    else lowestAccess.[lowestAccess.[b]]<-lowestAccess.[a]
   if (List.forall (fun e->unravel e=0) L) || (List.forall (fun e->unravel e=1) L)
    then cost
    else cost+breakWall tl
  else
   breakWall tl
|[]-> -20000000
System.Console.WriteLine(breakWall !edges)



System.Console.ReadLine()