open System.IO
open System

let inp = new StreamReader("input.txt")
let pr = new StreamWriter("output.txt")

let oneCase()=
 let n,p=inp.ReadLine().Split ' ' |> Array.map int |> function [|a;b|]->a,b |_->(0,0)
 let stuff=inp.ReadLine().Split ' ' |> Array.map int
 let l=ref 0  //left pointer
 let accSum=ref 0
 Array.mapi (fun r e->  //right pointer, they are inclusive
  accSum:= !accSum+e
  while !accSum>p && !l<=r do
   accSum:= !accSum-stuff.[!l]
   l:= !l+1
  r- !l+1
 ) stuff
  |> Array.sumBy int64
  |> pr.WriteLine

for e in 1..inp.ReadLine() |> int do
 pr.Write "Case #"
 pr.Write e
 pr.Write ": "
 try
  oneCase()
 with
 |e->printfn "%A" e
 //Console.ReadLine() |> ignore
pr.Flush()
inp.Close()
pr.Close()