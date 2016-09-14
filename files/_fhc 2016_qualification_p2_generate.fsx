open System.IO
open System

let pr=new StreamWriter "input.txt"
let gen=Random()
let cases=100
pr.WriteLine cases
for e in 1..cases do
 printfn "%A" e
 let n=1000
 pr.WriteLine n
 let bl()=gen.Next 2=1
 for e in 1..n do
  (if bl() then '.' else 'X') |> pr.Write
 pr.WriteLine()
 for e in 1..n do
  (if bl() then '.' else 'X') |> pr.Write
 pr.WriteLine()

pr.Flush()
