open System.IO
open System

let pr=new StreamWriter "input.txt"
let gen=Random()
let cases=100
pr.WriteLine cases
for e in 1..cases do
 printfn "%A" e
 let n=8
 let k=gen.Next(1,n)
 pr.Write n
 pr.Write ' '
 pr.WriteLine k

 for e in 1..n do
  {1..100000} |> Seq.iter (fun e->gen.Next(int 'a',int 'z'+1) |> char |> pr.Write)
  pr.WriteLine()
pr.Flush()
