open System
open System.IO
open System.Collections.Generic

let inp = new StreamReader "input.txt"
let pr = new StreamWriter "output.txt"

let oneCase() =
 let n=inp.ReadLine() |> int
 let pwn=
  Array.init n (fun _->inp.ReadLine().Split ' ' |> Array.map ((=) "1"))
 let win=
  Array.init n (fun e->[for ee in 0..n-1 do if pwn.[e].[ee] then yield ee])
 for e in 0..n-1 do pwn.[e].[e]<-true
 //printfn "%A" win
 let transform (ll:int list[])=
  Array.mapi (fun i e->
   List.collect (fun target->
    List.collect (fun thismask->
     List.filter (fun othermask->
      thismask&&&othermask=0
     ) ll.[target]
      |> List.map (fun msk->thismask+msk)
    ) e
   ) win.[i]
    |> List.sort
    |> List.fold (fun acc e->
        match acc with
        |[]->[e]
        |hd::tl->
         if e=hd then acc else e::acc
       ) []
  ) ll
 let h=
  match n with
  |1->0
  |2->1
  |4->2
  |8->3
  |16->4
  |_->failwith "GG"
 let rec ( *** ) a b=
  match b with
  |0->1
  |_->a*(a***(b-1))
 let mutable item=Array.init n (fun e->[ 2***e ])
 //printfn "%A" item
 let accMax=Array.create n 0
 for e in 1..h do
   item<-transform item
   Array.iteri (fun i e_->
    if e_<>[] then
     accMax.[i]<-e
   ) item
 let place=function
 |0->n/2+1
 |1->n/2/2+1
 |2->n/2/2/2+1
 |3->n/2/2/2/2+1
 |4->1
 Array.map place accMax
  |> Array.iteri (fun i e->
      pr.Write e
      pr.Write ' '
      pr.WriteLine (if Array.exists not pwn.[i] then n/2+1 else 1)
     )
   

for e in 1..inp.ReadLine() |> int do
 printfn "%A" e
 pr.Write "Case #"
 pr.Write e
 pr.WriteLine ": "
 try
  oneCase() //|> pr.WriteLine
 with
 |e->printfn "%A" e

pr.Flush()
pr.Close()
Console.ReadLine()