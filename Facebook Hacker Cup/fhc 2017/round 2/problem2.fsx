open System.IO
open System
//let stdin = new StreamReader "input.txt"
//let stdout = new StreamWriter  "output.txt"
let i() = stdin.ReadLine()
let ii() = i().Split() |> Array.map int64

let case() =
  let n = int(i())
  let read() =
    let [|x1; a; b; c|] = ii()
    let allX = Array.create n 0L
    allX.[0] <- x1
    for e in 1..n-1 do allX.[e] <- (a * allX.[e-1] + b) % c + 1L
    allX
  let allTents = Array.zip (read()) (read()) |> Array.map (fun (a, b) -> (a-b, a+b))
  //printfn "%A" allTents
  let tents = ref []
  let check (x, y) =
    let maxY, maxX, fl = ref 0, ref 0, ref false
    tents :=
     List.filter (fun (x', y') ->
      if x' >= x && y' <= y then false
      else
        if x' <= x && y' >= y then fl := true
        elif x' <= x then maxY := max !maxY y'
        else maxX := max !maxX x'
        true
      ) !tents
    maxY, maxX, fl
  Array.map check allTents

for e in 1..int(i()) do
  printfn "%A" e
  try
    stdout.WriteLine (sprintf "Case #%i: %A" e (case()))
  with
  |e ->
    printfn "%A" e
    System.Console.ReadLine() |> ignore
stdout.Flush()