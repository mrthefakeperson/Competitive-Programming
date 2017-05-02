open System.IO
let stdin = new StreamReader "input.txt"
let stdout = new StreamWriter  "output.txt"
let i() = stdin.ReadLine()
let ii() = i().Split() |> Array.map int

let case() =
  let [|n; r|] = ii()
  let points = List.init n (fun _ -> match ii() with [|x; y|] -> (x,y))
  let ensquare (x,y,x',y') ll =
    let inSquare (xx,yy) = x <= xx && xx <= x' && y <= yy && yy <= y'
    List.partition inSquare ll
  let allSquares (x,y) = [(x,y,x+r,y+r); (x,y-r,x+r,y); (x-r,y,x,y+r); (x-r,y-r,x,y)]
  let bestSquare ll =
    let allSq = List.collect allSquares ll
    let numberInside xyx'y' =
      let a, b = ensquare xyx'y' ll
      List.length a
    List.map numberInside allSq
     |> List.fold max 0
  List.collect allSquares points
   |> List.map (fun xy ->
        let a, b = ensquare xy points
        List.length a + bestSquare b
       )
   |> List.fold max 0

for e in 1..int(i()) do
  printfn "%A" e
  try
    stdout.WriteLine (sprintf "Case #%i: %i" e (case()))
  with
  |e ->
    printfn "%A" e
    System.Console.ReadLine() |> ignore
stdout.Flush()