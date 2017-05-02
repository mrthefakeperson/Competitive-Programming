open System.IO

let inp, pr = stdin, stdout
//let inp, pr = new StreamReader "input.txt", new StreamWriter "output.txt"
let i = inp.ReadLine
let ii() = Array.map int (i().Split ' ')

let check ll =
  let n = String.concat "" (Array.map string ll) |> int
  {n.. -1..1}
   |> Seq.find (fun e ->
        let x = (string e).ToCharArray()
        x = Array.sort x
       )
   |> string
   |> fun e -> printfn "%s" e; e
let case() =
  let number = (string (int64 (i()) + 1L)).ToCharArray() |> Array.map (string >> int) |> Array.append [|0|]
  let tryDigit i =
    let yld = Array.copy number
    yld.[i] <- yld.[i] - 1    // 0 -> -1
    for e in i + 1..number.Length - 1 do
      yld.[e] <- 9
    yld
  let isTidy (ll:int[]) =
    Seq.forall (fun e -> ll.[e] >= ll.[e-1]) {1..ll.Length - 1}
  let rec findLargest i =
    let rr = tryDigit i
    if isTidy rr
     then rr
     else findLargest (i - 1)
  findLargest (number.Length - 1)
   |> Array.map string
   |> String.concat ""
   |> int64 |> string
 //  |> fun e -> if e = check number then e else failwith "not right"

for e in 1..int(i()) do
  printfn "%A" e
  pr.WriteLine(sprintf "Case #%i: %s" e (case()))
pr.Flush()