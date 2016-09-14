open System
open System.IO
open System.Collections.Generic

let inp = new StreamReader "input.txt"
let pr = new StreamWriter "output.txt"

let oneCase() =
 let n,a,b=inp.ReadLine().Split ' ' |> Array.map int |> function [|a;b;c|]->a,b,c |_->failwith "GG"
 let steps=inp.ReadLine().Split ' ' |> Array.map int
 let oneCycle=Array.sumBy (fun e->float e/(float b-float a)*float e/2.) steps
 let cycleLength=Array.sumBy int64 steps
 let areaUnderGraph e=
  let ccls=float(e/cycleLength)*oneCycle
  let rm=e%cycleLength
  let mutable ptr,acc,accc=0,0L,0.
  while ptr<steps.Length && acc+int64 steps.[ptr]<=rm do
   acc<-acc+int64 steps.[ptr]
   accc<-accc+float steps.[ptr]/2./float(b-a)*float steps.[ptr]
   ptr<-ptr+1
  let last=rm-acc
  let l_=float last*float last/2./(float(b-a))
  //printfn "%A: %A,%A %A,%A %A,%A" e last l_ rm accc (float(e/cycleLength)) ccls
  l_+accc+ccls
 areaUnderGraph (int64 b)-areaUnderGraph (int64 a)
   

for e in 1..inp.ReadLine() |> int do
 printfn "%A" e
 pr.Write "Case #"
 pr.Write e
 pr.Write ": "
 try
  (oneCase().ToString "0.00000000") |> pr.WriteLine
 with
 |e->printfn "%A" e

pr.Flush()
pr.Close()
Console.ReadLine()