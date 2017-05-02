open System.IO

//let inp, pr = stdin, stdout
let inp, pr = new StreamReader "input.txt", new StreamWriter "output.txt"
let i = inp.ReadLine
let ii() = Array.map int (i().Split ' ')

let case() =
  let [|s; k|] = i().Split ' '
  let s = Array.ofSeq s |> Array.map ((=) '-')
  let k = int k
  let flipK i =
    for e in i..i + k - 1 do
      s.[e] <- not s.[e]
  {0..s.Length - k}
   |> Seq.filter (fun e ->
        if s.[e] then
          flipK e
          true
        else false
       )
   |> Seq.length
   |> fun ans ->
        if Array.exists id s
         then "IMPOSSIBLE"
         else string ans

for e in 1..int(i()) do
  printfn "%A" e
  pr.WriteLine(sprintf "Case #%i: %s" e (case()))
pr.Flush()