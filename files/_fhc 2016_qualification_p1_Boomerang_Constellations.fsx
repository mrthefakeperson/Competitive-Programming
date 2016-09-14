open System.IO
open System
open System.Collections.Generic

let inp = new StreamReader("input.txt")
let pr = new StreamWriter("output.txt")

let oneCase()=
 let items=
  List.init (inp.ReadLine() |> int)
   (fun _->match inp.ReadLine().Split ' ' |> Array.map int with [|a;b|]->(a,b) |_->(-343534543,-45455555))
 let rec itr acc=function
 |[]->acc
 |(hdx,hdy)::tl->
  let mm=Dictionary<int,int>()
  items
   //|> List.map (fun (x,y)->(x-hdx)*(x-hdx)+(y-hdy)*(y-hdy))
   |> List.map (fun (x,y)->
       let e=(x-hdx)*(x-hdx)+(y-hdy)*(y-hdy)
       if mm.ContainsKey e |> not then mm.[e]<-0
       mm.[e]<-mm.[e]+1
       e
      )
   |> List.sumBy (fun e->
       let rr=mm.[e]*(mm.[e]-1)/2
       mm.[e]<-0
       rr
      )
   (*
   |> List.sort
   |> List.fold (fun acc e->
       match acc with
       |[]->[(e,1)]
       |(a,q)::tl when a=e->(a,q+1)::tl
       |_->(e,1)::acc
      ) []
   |> List.sumBy (fun (_,q)->(q*q-q)/2)
   *)
   |> (+) acc |> itr <| tl
 itr 0 items
  |> pr.WriteLine

for e in 1..inp.ReadLine() |> int do
 printfn "%A" e
 pr.Write "Case #"
 pr.Write e
 pr.Write ": "
 oneCase()
 //Console.ReadLine() |> ignore
pr.Flush()
inp.Close()
pr.Close()