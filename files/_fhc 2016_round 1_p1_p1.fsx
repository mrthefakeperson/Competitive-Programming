open System
open System.IO

let inp = new StreamReader "input.txt"
let pr = new StreamWriter "output.txt"


let oneCase() =
 let n = inp.ReadLine() |> int
 let numbers = inp.ReadLine().Split ' ' |> Array.map int64 |> Array.append [|-10000L|]
 let help = Array.create (n+1) 0
 for e in 1..n do
  //printfn "%A" e
  help.[e]<-
    let mutable ll,pt=[(numbers.[e],e)],e
    for _ in 1..3 do
     if pt-1<0 then ll<-(-10000,-1)::ll
     elif fst ll.Head<=numbers.[pt-1] then ll<-(-10000,-1)::ll
     elif fst ll.Head-numbers.[pt-1]<=10 then
      pt<-pt-1
      ll<-(numbers.[pt],pt)::ll
     else ll<-(fst ll.Head-10,-1)::ll
    ll
     |> List.map snd
     |> List.filter ((<>) -1)
     //|> fun e->printfn "%A" e;e
     |> List.minBy (fun e->help.[e-1])
     |> fun e->help.[e-1]+1
 //printfn "%A" help
 help.[n]*4-n
     
     

for e in 1..inp.ReadLine() |> int do
 printfn "%A" e
 pr.Write "Case #"
 pr.Write e
 pr.Write ": "
 try
  oneCase() |> pr.WriteLine
 with
 |e->
  printfn "%A" e
  Console.ReadLine() |> ignore

pr.Flush()
pr.Close()
Console.ReadLine()