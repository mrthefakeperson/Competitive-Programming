open System.IO
open System
open System.Collections.Generic

let pr=new StreamWriter "input.txt"
let gen=Random()
let cases=50
pr.WriteLine cases
for e in 1..cases do
 printfn "%A" e
 let used=Dictionary<int*int,bool>()
 let n=200
 pr.WriteLine n
 for e in 1..n do
  let mutable x,y=gen.Next(-10000,10000),gen.Next(-10000,10000)
  while used.ContainsKey(x,y) do
   x<-gen.Next(-10000,10000)
   y<-gen.Next(-10000,10000)
  used.[(x,y)]<-true
  pr.Write x
  pr.Write ' '
  pr.WriteLine y

pr.Flush()
