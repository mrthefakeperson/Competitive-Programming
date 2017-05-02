module Matching
open System
open System.Collections.Generic

let cover (adj':bool[][])=
  let elements=adj'.Length
  let adj=Array.init (2*elements+1) (fun _->[])
  let capacityState= //Dictionary<int*int,bool>()
    Array2D.create (2*elements+1) (2*elements+1) false
  let mutable allEdges=[]
  for e in 0..elements-1 do
    for ee in 0..elements-1 do
      if adj'.[e].[ee] then
        adj.[e]<-(ee+elements)::adj.[e]
        adj.[ee+elements]<-e::adj.[ee+elements]
        capacityState.[e,ee+elements]<-false
        capacityState.[ee+elements,e]<-true
        allEdges<-(e,ee+elements)::allEdges
  for e in elements..2*elements-1 do
    adj.[e]<-(2*elements)::adj.[e]
    capacityState.[e,2*elements]<-false
    capacityState.[2*elements,e]<-true
  
  let rec search (visited:int[])=function
    |node when node=2*elements->true
    |node->
      adj.[node]
       |> List.filter (fun e->visited.[e]= -2 && not capacityState.[node,e])
       |> List.exists (fun e->
            visited.[e]<-node
            search visited e
           )
  for e in 0..elements-1 do
    let visited=Array.create (2*elements+1) -2
    visited.[e]<- -1
    let rec backtrack e=
      match visited.[e] with
      | -2 | -1->[]
      |prev->(prev,e)::backtrack prev
    if search visited e then
      backtrack (2*elements)
       // |> fun e->printfn "%A" e;e
       |> List.iter (fun (a,b)->
            capacityState.[a,b]<-true
            capacityState.[b,a]<-false
           )
  let partition=Array.create (2*elements) false
  let usedEdges=List.filter (fun (a,b)->capacityState.[a,b]) allEdges
  List.iter (fun (a,b)->partition.[a]<-true) usedEdges
  let rec fixAssignments=function
    |[]->()
    |ll->
      List.collect (fun e->
        List.filter (fun e->
          if not partition.[e]
           then
            partition.[e]<-true
            true
           else false
         ) adj.[e]
       ) ll
       |> List.choose (fun e->List.tryFind (fun ee->ee<>2*elements && capacityState.[ee,e]) adj.[e])
       |> fun e->
            List.iter (fun e->partition.[e]<-false) e
            fixAssignments e
  [0..elements-1]
   |> List.filter (fun e->not partition.[e])
   |> fixAssignments
  let rr=List.filter (fun e->partition.[e])
  rr [0..elements-1],rr [elements..2*elements-1] |> List.map ((+) -elements),usedEdges
  
let rec matching (originalCosts:int64[][]) (costs:int64[][])=
  let elements=costs.Length
  //printfn "matching: %A \n\t%A" originalCosts costs
  match cover (Array.map (Array.map ((=) 0L) ) costs) with
  |(a,b,_) when List.length a+List.length b<>elements->
    //printfn "matched into sets:\n\t%A \n\t%A" a b
    let r,c=Array.create elements false,Array.create elements false
    List.iter (fun e->r.[e]<-true) a
    List.iter (fun e->c.[e]<-true) b
    let change=
      seq{
        for e in 0..elements-1 do
          for ee in 0..elements-1 do
            if not r.[e] && not c.[ee] then yield costs.[e].[ee]
      }
       |> Seq.min
    for e in 0..elements-1 do
      for ee in 0..elements-1 do
        costs.[e].[ee]<-costs.[e].[ee]-change
    List.iter (fun e->
      for ee in 0..elements-1 do costs.[e].[ee]<-costs.[e].[ee]+change
     ) a
    List.iter (fun e->
      for ee in 0..elements-1 do costs.[ee].[e]<-costs.[ee].[e]+change
     ) b
    matching originalCosts costs
  |(_,_,matching)->
    matching
     |> List.sort
     |> List.map (fun (a,b)->originalCosts.[a].[b-elements])
     |> Array.ofList

let solve a=
  let startTime=Environment.TickCount
  let state=
    Array.map (fun e->
      let m=Array.min e
      Array.map ((+) -m) e
     ) a
  if a<>[||] then
    for e in 0..a.[0].Length-1 do
      let sb=Seq.init a.Length (fun ee->state.[ee].[e]) |> Seq.min
      for ee in 0..a.Length-1 do
        state.[ee].[e]<-state.[ee].[e]-sb
  matching a state
  (*
  let startTime2=Environment.TickCount
  let rr=matching a state
  printfn "time taken: %A ms, %A ms" (Environment.TickCount-startTime) (Environment.TickCount-startTime2)
  rr
  *)