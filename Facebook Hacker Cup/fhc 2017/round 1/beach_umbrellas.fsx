open System.IO
let stdin = new StreamReader "input.txt"
let stdout = new StreamWriter  "output.txt"
let i() = stdin.ReadLine()
let ii() = i().Split() |> Array.map int

let M = 1000000007
let (+%) a b = (a+b) % M
let ( *% ) a b = int64 a * int64 b % int64 M |> int
let rec ( **% ) a = function
  |0 -> 1
  |b when b % 2 = 1 -> a *% (a **% (b-1))
  |b ->
    let half = a **% (b/2)
    half *% half
let ( /% ) a b = a *% (b **% (M-2))
let fctrl = Array.create 100000 0
fctrl.[0] <- 1
for e in 1..99999 do fctrl.[e] <- fctrl.[e-1] *% e
let factorial x = fctrl.[x] //Seq.fold ( *% ) 1 {1..x}
let multiplyRange a b =
  let mutable acc = 1L
  for e in a..b do acc <- acc * int64 e % int64 M
  int acc
let choose n k = // factorial n /% factorial k /% factorial (n-k)
  let k = max k (n-k)
  (multiplyRange (k+1) n)
  //(Seq.map (fun e -> e % M) {k+1..n} |> Seq.fold ( *% ) 1)
   /% factorial (n-k)

let case() =
  let [|n; m|] = ii()
  let ll = Array.init n (fun e -> int(i()))
  let k = 2 * Array.max ll
  let overflow2 k =    //number of ways to choose (a,b) from umbrellas such that a+b >= k
    let sw = Array.create (k+2) 0
    Array.iter (fun e ->
      let e = min e k
      sw.[1] <- sw.[1] + 1
      sw.[e+1] <- sw.[e+1] - 1
     ) ll
    for e in 1..k+1 do sw.[e] <- sw.[e] + sw.[e-1]
    sw.[k] <- 0
    for e in k.. -1..0 do sw.[e] <- sw.[e] +% sw.[e+1]
    Array.sumBy (fun e ->
      let e = min e (k-1)
      let v = max 0 (2*e - (k-1))
      int64 (sw.[k-e] - v)
     ) ll
     |> fun e -> (int(e%int64 M)+M)%M
  let overflowPair = Array.init (k+1) (function 0 -> 0 | e -> overflow2 e)
  let overflowOne = Array.create (Array.max ll + 2) 0
  Array.iter (fun e ->
    overflowOne.[1] <- overflowOne.[1] + 1
    overflowOne.[e+1] <- overflowOne.[e+1] - 1
   ) ll
  for e in 1..Array.max ll+1 do overflowOne.[e] <- overflowOne.[e] + overflowOne.[e-1]

  let addSpaces a b = if a < 0 || b <= 0 then 0 else choose (b + a - 1) a
  let x = m - Array.sumBy ((*) 2) ll - 1
  //printfn "%A" x
  if n = 1 then m
  else
    factorial n *% addSpaces x (n+1)
    +%(Seq.mapi (fun k e ->
        addSpaces (x + k) n *% e *% 2
        ) overflowOne
        |> Seq.fold (+%) 0
        |> ( *% ) (factorial (n-1)) )
    +%(Seq.mapi (fun k e ->
        addSpaces (x + k) (n-1) *% e
        ) overflowPair
        |> Seq.fold (+%) 0
        |> ( *% ) (factorial (n-2)) )

for e in 1..int(i()) do
  printfn "%A" e
  try
    stdout.WriteLine (sprintf "Case #%i: %i" e (case()))
  with
  |e ->
    printfn "%A" e
    System.Console.ReadLine() |> ignore
stdout.Flush()