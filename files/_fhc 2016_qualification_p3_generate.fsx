open System.IO
open System

let pr=new StreamWriter "input.txt"
let gen=Random()
let cases=40
pr.WriteLine cases
for e in 1..cases do
 printfn "%A" e
 let n=100
 let p=gen.Next(1,1000000001)
 pr.Write n
 pr.Write ' '
 pr.WriteLine p
 for e in 1..n-1 do
  pr.Write (gen.Next(1,1000000001))
  pr.Write ' '
 pr.WriteLine(gen.Next(1,1000000001))

pr.Flush()
