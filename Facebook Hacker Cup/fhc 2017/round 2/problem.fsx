open System.IO
let stdin = new StreamReader "input.txt"
let stdout = new StreamWriter  "output.txt"
let i() = stdin.ReadLine()
let ii() = i().Split() |> Array.map int

let case() =
  let [|n; m; k|] = ii()
  let fit a b =
    if a % b = 0
     then a/b
     else a/b+1
  let p, q = min n m, max n m
  let answer1 =
    if k + 1 > p || 2*k + 3 > q
     then -1
     else fit p k
  let answer2 =
    if 2*k + 3 > q || 2*k + 1 > p
     then -1
     else fit (k+2) k + 2
  match answer1, answer2 with
  | -1, a | a, -1 -> a
  | a, b -> min a b

for e in 1..int(i()) do
  printfn "%A" e
  try
    stdout.WriteLine (sprintf "Case #%i: %i" e (case()))
  with
  |e ->
    printfn "%A" e
    System.Console.ReadLine() |> ignore
stdout.Flush()