let ll=Array.map int (System.Console.In.ReadLine().Split [|' '|])
let n,m,t=ll.[0],ll.[1],ll.[2]
let hall:int list[]=Array.init (n+1) (fun _->[])
for e in 1..m do
 let lL=Array.map int (System.Console.In.ReadLine().Split [|' '|])
 let src,dest=lL.[0],lL.[1]
 hall.[src]<-dest::hall.[src]
//(x,y)->time it takes to go from x to y; 0 unknown; -1 impossible
//let visited=Array2D.init (n+1) (n+1) (fun _ _->[])
//for e in hall do printfn "%A" e
let wholeFloor=Array2D.init (n+1) (n+1) (fun _ _->0)
let q=System.Console.In.ReadLine()|>int
for eee in 1..q do
 let lL=Array.map int (System.Console.In.ReadLine().Split [|' '|])
 let src,dest=lL.[0],lL.[1]
 if wholeFloor.[src,dest]<>0 then
  if wholeFloor.[src,dest]= -1 then System.Console.Out.WriteLine("Not enough hallways!")
  else System.Console.Out.WriteLine(wholeFloor.[src,dest]*t)
 else
  let mutable searchList,counter,exists=[src],0,true
  let visited:bool[]=Array.zeroCreate (n+1)
  while exists && searchList.Length<>0 do
   counter<-counter+1
   let mutable Nlist=[]
   for e in searchList do
    for e2 in hall.[e] do
     if not visited.[e2] then
      Nlist<-e2::Nlist
      visited.[e2]<-true
      if e2=dest then exists<-false
      wholeFloor.[src,e2]<-counter
   searchList<-Nlist
   //printfn "%A;%A" searchList Nlist
  if searchList.Length=0 then
   wholeFloor.[src,dest]<- -1
   System.Console.Out.WriteLine("Not enough hallways!")
  else System.Console.Out.WriteLine(counter*t)