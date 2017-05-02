open System.IO

//let inp, pr = stdin, stdout
let inp, pr = new StreamReader "input.txt", new StreamWriter "output.txt"
let i = inp.ReadLine
let ii() = Array.map int (i().Split ' ')

let case() =
  let [|r; c|] = ii()
  let grid = Array.init r (fun _ -> i().ToCharArray())
  let x =
    Array.map (fun (row:char[]) ->
      for e in 1..c - 1 do
        if row.[e] = '?' then row.[e] <- row.[e - 1]
      for e in c - 2.. -1..0 do
        if row.[e] = '?' then row.[e] <- row.[e + 1]
      String.concat "" (Array.map string row)
     ) grid
  for e in 1..r - 1 do
    if String.forall ((=) '?') x.[e] then x.[e] <- x.[e - 1]
  for e in r - 2.. -1..0 do
    if String.forall ((=) '?') x.[e] then x.[e] <- x.[e + 1]

  // verify
  if Array.exists (String.exists ((=) '?')) x then failwith "failed"

  Array.iter (pr.WriteLine:string->unit) x

for e in 1..int(i()) do
  printfn "%A" e
  pr.WriteLine(sprintf "Case #%i:" e)
  case()
  //pr.WriteLine(sprintf "Case #%i: %s" e (case()))
pr.Flush()