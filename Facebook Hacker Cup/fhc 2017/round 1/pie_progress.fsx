open System.IO
let stdin = new StreamReader "input.txt"
let stdout = new StreamWriter  "output.txt"
let i() = stdin.ReadLine()
let ii() = i().Split() |> Array.map int

let case() =
  let [|n; m|] = ii()
  let prices =
    let buyIndexPrice (ll:int[]) =
      let ll = Array.append [|0|] (Array.sort ll)
      for e in 1..ll.Length-1 do
        ll.[e] <- ll.[e] + ll.[e-1]
      for e in 0..ll.Length-1 do
        ll.[e] <- ll.[e] + e*e
      ll
    Array.init n (fun _ -> buyIndexPrice (ii()))
  let visited = Array2D.init (n+1) (n+1) (fun _ _ -> -1)
  //days left <= pies left
  //can't buy all the pies on the last day
  let rec f daysLeft piesLeft =
    match daysLeft, piesLeft with
    |(0, 0) -> 0
    |(0, _) -> -1
    |_ ->
      if visited.[daysLeft, piesLeft] = -1 then
        visited.[daysLeft, piesLeft] <-
          {0..min m piesLeft}
           |> Seq.minBy (fun k ->
                match f (daysLeft-1) (piesLeft-k) with
                | -1 -> 99999999
                | e -> e + prices.[daysLeft-1].[k]
               )
           |> fun k ->
                match f (daysLeft-1) (piesLeft-k) with
                | -1 -> 99999999
                | e -> e + prices.[daysLeft-1].[k]
      visited.[daysLeft, piesLeft]
  f n n

for e in 1..int(i()) do
  printfn "%A" e
  try
    stdout.WriteLine (sprintf "Case #%i: %i" e (case()))
  with
  |e ->
    printfn "%A" e
    System.Console.ReadLine() |> ignore
stdout.Flush()