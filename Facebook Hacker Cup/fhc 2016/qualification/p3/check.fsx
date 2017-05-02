open System.IO
open System

let inp = new StreamReader "input.txt"
let ans = new StreamReader "output.txt"

let oneCase()=
 let n,p=match inp.ReadLine().Split ' ' with [|a;b|]->(int a,int64 b) |_->(34234,-5667L)
 let items=inp.ReadLine().Split ' ' |> Array.map int64
 let mutable cnt=0
 for e in 0..n-1 do
  for ee in e..n-1 do
   if Array.sum items.[e..ee]<=p then
    cnt<-cnt+1
 cnt

for e in 1..inp.ReadLine() |> int do
 //printfn "%A" e
 let a=try oneCase() with |e->printfn "%A" e;-454
 if a<>(ans.ReadLine().Split(' ').[2] |> int) then printfn "wrong answer case %A: should be %A" e a
 //Console.ReadLine() |> ignore
printfn "done"
Console.ReadLine()