open System.IO
open System.Collections.Generic

let inp, pr = stdin, stdout
//let inp, pr = new StreamReader "input.txt", new StreamWriter "output.txt"
let i = inp.ReadLine
let ii() = Array.map int (i().Split ' ')

let case() =
  let [|selfH; selfA; targetH; targetA; b; d|] = ii()
  let visited = HashSet()
  let rec src = function
    |[] -> None
    |ll when List.exists (fun (h, a, tH, tA) -> tH <= 0) ll -> Some 0
    |ll ->
      List.collect (fun ((h, a, tH, tA) as e) ->
        if h <= 0 then []
        else
          let attack = h - tA, a, tH - a, tA
          let buff = h - tA, a + b, tH, tA
          let cure = selfH - tA, a, tH, tA
          let debuff = h - max 0 (tA - d), a, tH, max 0 (tA - d)
          List.filter (fun e ->
            if visited.Contains e then false
            else
              visited.Add e
              true
           ) [attack; buff; cure; debuff]
       ) ll
       |> src
       |> function Some x -> Some (x + 1) | None -> None
  match src [(selfH, selfA, targetH, targetA)] with
  |Some x -> string x
  |None -> "IMPOSSIBLE"

for e in 1..int(i()) do
  printfn "%A" e
  try pr.WriteLine(sprintf "Case #%i: %s" e (case()))
  with
   ex ->
    printfn "%A" ex
    ignore (stdin.ReadLine())
pr.Flush()