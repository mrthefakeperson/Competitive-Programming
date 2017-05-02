open System.IO
open System

let pr = new StreamWriter "input.txt"
let gen = Random()

let _1 generator =
  let generator = generator 1
  let t = generator 100
  pr.WriteLine (t:int)
  for e in 1..t do
    let n, m = generator 300, generator 300
    pr.WriteLine (sprintf "%i %i" n m)
    for e in 1..n do
      Seq.init m (fun _ -> generator 1000000)
       |> Seq.map string
       |> String.concat " "
       |> pr.WriteLine

let _2 generator =
  let generator = generator 1
  let t = generator 50
  pr.WriteLine (t:int)
  for e in 1..t do
    let n, r = generator 50, generator 1000000000
    pr.WriteLine (sprintf "%i %i" n r)
    for e in 1..n do
      let x, y = generator 1000000000, generator 1000000000
      pr.WriteLine (sprintf "%i %i" x y)

let _3 generator =
  let t = generator 1 100
  pr.WriteLine (t:int)
  for e in 1..t do
    let n, m, k = generator 2 100, generator 1 5000, generator 1 5000
    pr.WriteLine (sprintf "%i %i %i" n m k)
    for e in 1..m do
      let a, b, g = gen.Next(1, n+1), gen.Next(1, n+1), generator 1 1000
      pr.WriteLine (sprintf "%i %i %i" a b g)
    for e in 1..k do
      let s, d = gen.Next(1, n+1), gen.Next(1, n+1)
      pr.WriteLine (sprintf "%i %i" s d)

let _4 generator =
  let generator = generator 1
  let t = generator 100
  pr.WriteLine (t:int)
  for e in 1..t do
    let n, m = generator 2000, generator 1000000000
    pr.WriteLine (sprintf "%i %i" n m)
    for e in 1..n do
      let r = generator 2000
      pr.WriteLine r

let rng a b = gen.Next(a, b+1)
_4 rng
pr.Flush()