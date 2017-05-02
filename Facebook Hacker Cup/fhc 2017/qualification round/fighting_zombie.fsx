open System.IO
open System

let inp = new StreamReader "input.txt"
let pr = new StreamWriter "output.txt"
let i() = inp.ReadLine().Trim()
let ii() = Array.map int (i().Split ' ')

let ( *-- ) (a:float[]) (b:float[]) =
  let yld = Array.create (a.Length + b.Length - 1) 0.
  for e in 0..a.Length - 1 do
    for ee in 0..b.Length - 1 do
      yld.[e+ee] <- yld.[e+ee] + a.[e]*b.[ee]
  let allPossibilities = Array.sum yld
  Array.map (fun e -> e / allPossibilities) yld
let probabilities =
  Array2D.init 21 21 (fun x y ->
    let yld =
      Seq.init x (fun _ -> Array.append [|0.|] (Array.create y 1.))
       |> Seq.fold ( *-- ) [|1.|]
    for e in yld.Length-2.. -1..0 do
      yld.[e] <- yld.[e] + yld.[e+1]
    yld
   )

let case health spells (allSpells:(int*int*int)[]) =
  allSpells
   |> Array.map (fun (x, y, v) ->
        let threshold = health - v
        if threshold > probabilities.[x,y].Length - 1 then 0.
        elif threshold < 0 then 1.
        else probabilities.[x,y].[threshold]
       )
   |> Array.max

let gen = Random()
let check health spells (allSpells:(int*int*int)[]) =
  let rec roll x y v =
    if x = 0
     then v
     else gen.Next y + 1 + roll (x-1) y v
  Array.map (fun (x,y,v) ->
    Seq.init 10000000 (fun _ -> roll x y v)
     |> Seq.filter ((<=) health)
     |> Seq.length
     |> fun e -> float e / 10000000.
   ) allSpells
   |> Array.max

for e in 1..int(i()) do
  let [|health; spells|] = ii()
  let allSpells =
    i().Split ' '
     |> Array.map (fun (e:string) ->
          if e.Contains "+" then
            match e.Split '+' with [|r; v|] -> (r, int v)
          elif e.Contains "-" then
            match e.Split '-' with [|r; v|] -> (r, -(int v))
          else (e, 0)
         )
     |> Array.map (fun (rolls, value) ->
          match rolls.Split 'd' with
            [|x; y|] -> (int x, int y, value)
         )
  pr.Write (sprintf "Case #%i: " e)
  pr.WriteLine (case health spells allSpells)

  //printfn "%A" (check health spells allSpells)
pr.Flush()
//stdin.ReadLine()