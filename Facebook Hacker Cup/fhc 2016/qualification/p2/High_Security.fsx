open System.IO
open System

let inp = new StreamReader("input.txt")
let pr = new StreamWriter("output.txt")

let oneCase()=
 let n=inp.ReadLine() |> int
 let a=inp.ReadLine().ToCharArray() |> Array.map (function |'.'->true |_->false)
 let b=inp.ReadLine().ToCharArray() |> Array.map (function |'.'->true |_->false)
 let goThrough (ll:bool[])=
  let mutable ct=
   if ll.[0] then 1 else 0
  for e in 1..ll.Length-1 do
   if (not ll.[e-1]) && ll.[e] then ct<-ct+1
  ct
 let amt=goThrough a+goThrough b |> ref
 //printfn "%A" !amt
 let fill (ll:bool[]) e=
  let mutable goL,goR=e,e
  ll.[e]<-false
  while goL-1>=0 && ll.[goL-1] do
   goL<-goL-1
   ll.[goL]<-false
  while goR+1<ll.Length && ll.[goR+1] do
   goR<-goR+1
   ll.[goR]<-false
 let go2 (ll:bool[]) (other:bool[])=
  for e in 0..ll.Length-1 do
   let left,right=
    (if e=0 then false else ll.[e-1]),(if e=ll.Length-1 then false else ll.[e+1])
   if ll.[e] && (not left && not right) && other.[e] then
    fill other e
    amt:= !amt-1
 go2 a b
 go2 b a
 pr.WriteLine !amt

for e in 1..inp.ReadLine() |> int do
 pr.Write "Case #"
 pr.Write e
 pr.Write ": "
 try
  oneCase()
 with
 |e->printfn "%A" e
 printfn "%A" e
 //Console.ReadLine() |> ignore
pr.Flush()
inp.Close()
pr.Close()