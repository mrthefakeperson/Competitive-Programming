open System.IO
open System

let inp = new StreamReader "input.txt"
let ans = new StreamReader "output.txt"

let oneCase()=
 let n=inp.ReadLine() |> int
 let points=
  List.init n (fun _->match inp.ReadLine().Split ' ' with [|a;b|]->(int a,int b) |_->(353,5555456))
 let dd (x,y) (xx,yy)=(xx-x)*(xx-x)+(yy-y)*(yy-y)
 let cnt=ref 0
 List.iteri (fun i e->
  List.iteri (fun ii ee->
   List.iteri (fun iii eee->
    if i<>ii && ii<>iii && i<>iii then
     if dd e ee=dd ee eee then cnt:= !cnt+1
   ) points
  ) points
 ) points
 !cnt/2

for e in 1..inp.ReadLine() |> int do
 let a=oneCase()
 if a<>(ans.ReadLine().Split(' ').[2] |> int) then printfn "wrong answer case %A: should be %A" e a
 //Console.ReadLine() |> ignore
printfn "done"
Console.ReadLine()