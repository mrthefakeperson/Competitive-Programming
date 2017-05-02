open System.IO
open System

let inp = new StreamReader "input.txt"
let pr = new StreamWriter "output.txt"
let i() = inp.ReadLine().Trim()
let ii() = Array.map int (i().Split ' ')

let case n weights =
  weights
   |> Array.map (fun e -> 50 / e + (if 50 % e > 0 then 1 else 0))
   |> Array.sort
   |> Array.fold (fun (acc, ans) e ->
        if acc + e > n
         then (acc, ans)
         else (acc + e, ans + 1)
       ) (0, 0)
   |> snd

for e in 1..int(i()) do
  let n = int(i())
  let w = Array.init n (fun _ -> int(i()))
  pr.Write (sprintf "Case #%i: " e)
  pr.WriteLine (case n w)
pr.Flush()