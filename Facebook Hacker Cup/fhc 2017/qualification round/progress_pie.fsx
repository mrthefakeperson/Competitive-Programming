open System.IO
open System

let inp = new StreamReader "input.txt"
let pr = new StreamWriter "output.txt"
let i() = inp.ReadLine().Trim()
let ii() = Array.map int (i().Split ' ')

let case p x y =
  let p, x, y = float p / 100., float x, float y
  let inCircle = Math.Sqrt((50.-x)*(50.-x)+(50.-y)*(50.-y)) <= 50.
  let inSector = Math.PI*2.*p > (Math.Atan2(x-50., y-50.)+Math.PI*2.)%(Math.PI*2.)
  if inCircle && inSector
   then "black"
   else "white"

for e in 1..int(i()) do
  let [|p; x; y|] = ii()
  pr.Write (sprintf "Case #%i: " e)
  pr.WriteLine (case p x y)
pr.Flush()
(*
Console.WindowWidth <- 105
let pie p =
  for e in 100.. -1..0 do
    for ee in 0..100 do
      printf "%c" (if case p ee e = "black" then 'B' else ' ')
    printfn""
  //while Environment.TickCount % 1000 > 0 do ()
  stdin.ReadLine() |> ignore
pie 0
pie 50
pie 100
*)