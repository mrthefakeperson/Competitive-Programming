#load "matchme.fsx"

open System.IO
open System

let gen=Random()
let case()=
  let pr=new StreamWriter "test.txt"
  pr.WriteLine 30
  for e in 1..30 do
    String.Join(" ",Array.init 30 (fun _->gen.Next 99999999))
     |> pr.WriteLine
  pr.Flush()
  pr.Close()

let solveCase()=
  let inp=new StreamReader "test.txt"
  let ii()=Array.map int (inp.ReadLine().Split ' ')
  match ii() with
  |[|s|]->
    try
      let time=Environment.TickCount
      Array.init s (fun _->Array.map int64 <| ii())
       |> Matching.solve
       |> printfn "%A"
      printfn "took %A ms" (Environment.TickCount-time)
    with
    |ex->printfn "%A" ex
  inp.Close()
while true do
  case()
  solveCase()
  Console.ReadLine() |> ignore