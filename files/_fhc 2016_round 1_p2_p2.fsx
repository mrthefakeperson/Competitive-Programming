open System
open System.IO
open System.Collections.Generic

let inp = new StreamReader "input.txt"
let pr = new StreamWriter "output.txt"


let oneCase() =
 let loads,amtWash,dryers,dryTime=match inp.ReadLine().Split ' ' |> Array.map int with [|a;b;c;d|]->(a,b,c,int64 d)
 printfn "%A %A %A %A" loads amtWash dryers dryTime
 let washers= 
  new SortedSet<(int64*int64)*int>()
 inp.ReadLine().Split ' ' |> Array.map int64 |> Array.mapi (fun i e->((e,e),i))
  |> Array.iter (fun e->ignore(washers.Add e))
 let dryersAv=
  new SortedSet<int64*int>()
 for e in 1..min loads dryers do dryersAv.Add(0L,e) |> ignore
 Array.init loads (fun _->
  let rr,iden=washers.Min
  washers.Remove(rr,iden) |> ignore
  washers.Add((fst rr+snd rr,snd rr),iden) |> ignore
  fst rr
 )
  //|> fun e-> printfn "%A" e;e
  |> Array.iter (fun e->
      let rr,iden=dryersAv.Min
      dryersAv.Remove(rr,iden) |> ignore
      dryersAv.Add(max rr e+dryTime,iden) |> ignore
     )
 fst dryersAv.Max 
     

for e in 1..inp.ReadLine() |> int do
 printfn "%A" e
 pr.Write "Case #"
 pr.Write e
 pr.Write ": "
 try
  oneCase() |> pr.WriteLine
 with
 |e->printfn "%A" e
 //Console.ReadLine() |> ignore

pr.Flush()
pr.Close()
Console.ReadLine()