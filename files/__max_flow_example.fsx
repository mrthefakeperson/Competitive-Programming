//example of a bipartite matching algorithm (max flow)
open System
open System.IO
open System.Collections.Generic

let check (inp:StreamReader) (ans:StreamReader)=
 let rPr()=match inp.ReadLine().Split ' ' with [|a;b|]->(int a,int b) |_->failwith "failed to read input"
 let n,m=rPr()
 let adj=Array.init (n+m) (fun _->[])  //adjacency for everything (sources shifted over by n)
 let flow=Dictionary<int*int,bool>()   //bipartite flow (0/1), accessed (max,min)
 let allEdges=List.init m (fun _->rPr()) |> List.map (fun (a,b)->(a-1,b-1))
 List.iteri (fun i (a,b)->
   let e=i+n
   adj.[e]<-[a;b]
   adj.[a]<-e::adj.[a]
   adj.[b]<-e::adj.[b]
 ) allEdges
 let resetFlow()=
  flow.Clear()
  List.iteri (fun i (a,b)->
   let e=i+n
   flow.[(e,a)]<-false
   flow.[(e,b)]<-false
  ) allEdges
 let pushPath (sinks:int[]) k e=
  let visited=Array.create (n+m) false
  let queue=ResizeArray<int*int>()  //current,prev
  queue.Add (e,-1)
  let pt=ref 0
  while !pt<queue.Count && not (fst queue.[!pt]<n && sinks.[fst queue.[!pt]]<k) do
   let place=fst queue.[!pt]
   visited.[place]<-true
   List.iter (fun dest->
    if not visited.[dest] then
     if place>dest
      then
       if not flow.[(place,dest)] then queue.Add (dest,place)
      else
       if flow.[(dest,place)] then queue.Add (dest,place)
   ) adj.[place]
   pt:= !pt+1
  if !pt=queue.Count
   then false
   else
    let mutable place,prev=queue.[!pt]
    sinks.[place]<-sinks.[place]+1
    if prev>place
     then flow.[(prev,place)]<-true
     else flow.[(place,prev)]<-false
    while prev<> -1 do
     pt:= !pt-1
     if fst queue.[!pt]=prev then
      place<-fst queue.[!pt]
      prev<-snd queue.[!pt]
      if prev>place
       then flow.[(prev,place)]<-true
       else flow.[(place,prev)]<-false
    true
 let attempt sinks k=
  resetFlow()
  let rr=
   {n..n+m-1}
    |> Seq.map (pushPath sinks k)
    |> Seq.fold (&&) true
  //printfn "k:%A\nsinks:%A" k sinks
  rr
 let slv()=
  let mutable place,jump= -1,n
  while jump>0 do
   if not(attempt (Array.create n 0) (place+jump))
    then place<-place+jump
   jump<-jump/2
  while not(attempt (Array.create n 0) (place+1)) do place<-place+1
  place+1
 let ans1,ans2=slv(),ans.ReadLine() |> int
 if ans1<>ans2
  then
   printfn "checker answer %A does not agree with %A" ans1 ans2
   ignore (Console.ReadLine())
  else
   printfn "good %A" ans1

 inp.Close()
 ans.Close()
 
try check (new StreamReader "input.txt") (new StreamReader "output.txt")
with
|e->printfn "%A" e
Console.ReadLine()
