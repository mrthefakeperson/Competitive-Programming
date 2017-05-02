open System.IO
//let stdin = new StreamReader "input.txt"
//let stdout = new StreamWriter  "output.txt"
let i() = stdin.ReadLine()
let ii() = i().Split() |> Array.map int64

let case() =
  let [|n; m|] = ii()
  let n = int n
  let read c d n =
    let [|x1; a; b|] = ii()
    let allX = Array.create n 0L
    allX.[0] <- x1
    for e in 1..n-1 do allX.[e] <- (a * allX.[e-1] + b) % c + d
    allX
  let w = read (int64 n) 1L (int m)
  let d = read 3L 0L (int m)
  let z = Array.map2 (fun w d -> max 1L (min (int64 n) (w+d-1L))) w d
  let s = read 100000000L 1L (int m)
  printfn "%A" w
  printfn "%A" z
  printfn "%A" s

for e in 1..int(i()) do
  printfn "%A" e
  try
    stdout.WriteLine (sprintf "Case #%i: %A" e (case()))
  with
  |e ->
    printfn "%A" e
    System.Console.ReadLine() |> ignore
stdout.Flush()