open System.IO
open System

let inp = new StreamReader "input.txt"
let ans = new StreamReader "output.txt"

let oneCase()=
 let n,k=match inp.ReadLine().Split ' ' with [|a;b|]->(int a,int b) |_->(34234,-5667)
 let items=Array.init n (fun _->inp.ReadLine())
 let editDistance (a:string) (b:string)=
  let mutable maxPrefix=0
  while maxPrefix<a.Length && maxPrefix<b.Length && a.[maxPrefix]=b.[maxPrefix] do
   maxPrefix<-maxPrefix+1
  a.Length+b.Length-2*maxPrefix
 let doit ll=
  let str=ref ""
  List.map (fun e->items.[e]) ll
   |> List.sumBy (fun e->
       let rr=editDistance !str e
       str:=e
       rr
      )
   |> (+) (editDistance !str "")
 let rec getCombo remain acc=
  if remain=0
   then doit acc
   else
    {0..n-1} |> Seq.filter (fun e->not (List.exists ((=) e) acc))
     |> Seq.map (fun e->getCombo (remain-1) (e::acc))
     |> Seq.min
 getCombo k [] + k

for e in 1..inp.ReadLine() |> int do
 //printfn "%A" e
 let a=try oneCase() with |e->printfn "%A" e;-454
 if a<>(ans.ReadLine().Split(' ').[2] |> int) then printfn "wrong answer case %A: should be %A" e a
 //Console.ReadLine() |> ignore
printfn "done"
Console.ReadLine()