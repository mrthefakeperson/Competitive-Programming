let gen = System.Random()
let next = gen.Next >> (+) 1
let pr = new System.IO.StreamWriter "input.txt"

let case() =
  let n, p = 50, 50
  pr.WriteLine(sprintf "%i %i" n p)
  Seq.init n (fun _ -> string(next 1))
   |> String.concat " "
   |> (pr.WriteLine:string -> unit)
  for e in 1..n do
    Seq.init p (fun _ -> string(next 1))
     |> String.concat " "
     |> (pr.WriteLine:string -> unit)

pr.WriteLine 1
case()
pr.Flush()