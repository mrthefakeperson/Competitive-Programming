open System
open System.IO

let inp = new StreamReader "input.txt"
let pr = new StreamWriter "output.txt"


let oneCase() =
 let n=int(inp.ReadLine())
 let a,b=inp.ReadLine(),inp.ReadLine()
 let equal=Array.init n (fun e->e+1)
 for e in 0..n-1 do
  if a.[e]=b.[e]
   then
    if e=0 then equal.[e]<-0 else equal.[e]<-equal.[e-1]
// printfn "%A,%A -> %A" a b equal
 let eq l r=equal.[r]<=l
 let mutable lpt,rpt,cnt=0,n-1,0
 while not (eq lpt rpt) do
  //printfn "%A,%A" lpt rpt
  lpt<-lpt+1
  rpt<-rpt-1
  while b.[lpt]=b.[lpt-1] do lpt<-lpt+1
  while b.[rpt]=b.[rpt+1] do rpt<-rpt-1
  cnt<-cnt+1
 cnt
     

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