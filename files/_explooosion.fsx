open System
open System.Collections.Generic

let n=stdin.ReadLine() |> int
let stuff=stdin.ReadLine().Split ' ' |> Array.map int
let _1s,_2s,rest=
  let no1s=Array.filter ((<>) 1) stuff
  if no1s=[||]
   then n-1,0,[|1|]
   else
    let no2s=Array.filter ((<>) 2) no1s
    if no2s=[||]
     then n-no1s.Length,no1s.Length-1,[|2|]
     else n-no1s.Length,no1s.Length-no2s.Length,no2s
//printfn "%A %A %A" _1s _2s rest
let gMin=Array.sum rest+2*_2s
let gMax=
  let making3s=Array.create 2000 0
  Array.iter (fun e->making3s.[e]<-making3s.[e]+1) rest
  making3s.[2]<-making3s.[2]+_2s
  //let making3s=SortedSet<int*int>(Array.append (Array.create _2s 2) rest |> Array.mapi (fun i e->(e,i)))
  for e in 2.._1s do
    match making3s.[1],making3s.[2] with
    |(0,0)->making3s.[1]<-1
    |(1,0)->
      making3s.[1]<-0
      making3s.[2]<-1
    |(0,k)->
      making3s.[2]<-k-1
      making3s.[3]<-making3s.[3]+1
  if _1s>0 then
    let i=Array.findIndex ((<>) 0) making3s
    making3s.[i]<-making3s.[i]-1
    making3s.[i+1]<-making3s.[i+1]+1
  let product=ref 1L
  Array.iteri (fun i e->
    for _ in 1..e do product:= !product*int64 i % 1000000007L
   ) making3s
  !product
stdout.WriteLine gMin
stdout.WriteLine gMax


Seq.fold (fun acc _->acc*1000L%1000000007L) 1L {1..99998}
 * 2L % 1000000007L
