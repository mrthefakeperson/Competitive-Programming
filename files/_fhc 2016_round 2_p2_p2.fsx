open System
open System.IO

let inp = new StreamReader "input.txt"
let pr = new StreamWriter "output.txt"


let oneCase() =
 let n,k,p=inp.ReadLine().Split ' ' |> function [|a;b;c|]->int a,int b,float c
 if k>n then 0.
 else
  let chances=
   Array.init (n+1) ((fun (distribution:float[]) e->
    if e=0
     then distribution.[0]<-1.
     else
      let buffer=Array.copy distribution
      for e in 0..Array.length distribution - 1 do
       distribution.[e]<-0.
      for e in 0..e-1 do
       distribution.[e]<-distribution.[e]+buffer.[e]*(1.-p)
       distribution.[e+1]<-distribution.[e+1]+buffer.[e]*p
    try
     Array.sum distribution.[k..]
    with
    |_->printfn "%A" distribution.[k];0.
   ) (Array.create (n+1) 0.))
  let optimal=Array.create (n+1) -1.
  optimal.[0]<-0.
  for e in 1..n do
   optimal.[e]<-
    {0..e-1}
     |> Seq.map (fun ee->
         optimal.[ee]+chances.[e-ee]
        )
     |> Seq.max
  optimal.[n]
      

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