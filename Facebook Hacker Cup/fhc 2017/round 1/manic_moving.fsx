open System.IO
let stdin = new StreamReader "input.txt"
let stdout = new StreamWriter  "output.txt"
let i() = stdin.ReadLine()
let ii() = i().Split() |> Array.map int

[<Literal>]
let Inf = 99999999
let case() =
  let add a b =
    match a,b with
    |Inf,_ | _,Inf -> Inf
    |_ -> a+b
  let [|n; m; k|] = ii()
  let adj = Array2D.create n n Inf
  for e in 1..m do
    let [|a; b; c|] = ii()
    let a,b = a-1,b-1
    adj.[a, b] <- min adj.[a, b] c
    adj.[b, a] <- min adj.[b, a] c
  for e in 0..n-1 do adj.[e, e] <- 0
  for e in 0..n-1 do
    for ee in 0..n-1 do
      for eee in 0..n-1 do
        adj.[ee, eee] <- min adj.[ee, eee] (add adj.[ee, e] adj.[e, eee])
  let shortestPath = adj

  let families = Array.init k (fun _ -> Array.map ((+) -1) (ii()))
  let time = Array2D.init k 2 (fun _ _ -> 0)
  time.[0,0] <- shortestPath.[0, families.[0].[0]]
  time.[0,1] <- Inf
  for e in 1..k-1 do
    let method1 s e =
      add (shortestPath.[s, families.[e-1].[1]])
       (shortestPath.[families.[e-1].[1], families.[e].[0]])
    let method2 s e =
      add (shortestPath.[s, families.[e].[0]])
       (shortestPath.[families.[e].[0], families.[e-1].[1]])
    let getRoute method' e =
      if e > 1 then
        let a = add (time.[e-1,0]) (method' families.[e-1].[0] e)
        let b = add (time.[e-1,1]) (method' families.[e-2].[1] e)
        min a b
      else add (time.[e-1,0]) (method' families.[e-1].[0] e)
    time.[e,0] <- getRoute method1 e
    time.[e,1] <- getRoute method2 e
  let a =
    add time.[k-1,0] shortestPath.[families.[k-1].[0], families.[k-1].[1]]
  let b =   // 1 or 2 families
    if time.[k-1,1] = Inf
     then Inf
     else add time.[k-1,1] shortestPath.[families.[k-2].[1], families.[k-1].[1]]
  match min a b with
  |Inf -> -1
  |e -> e

for e in 1..int(i()) do
  printfn "%A" e
  try
    stdout.WriteLine (sprintf "Case #%i: %i" e (case()))
  with
  |e ->
    printfn "%A" e
    System.Console.ReadLine() |> ignore
stdout.Flush()