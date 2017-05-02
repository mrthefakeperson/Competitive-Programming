open System.IO

let inp, pr = stdin, stdout
//let inp, pr = new StreamReader "input.txt", new StreamWriter "output.txt"
let i = inp.ReadLine
let ii() = Array.map int64 (i().Split ' ')
let debug e = printfn "debug: %A" e; e

let check n v =
  let a = Array.create n false
  let getNext() =
    let Ls = Array.create n 0
    for e in 1..Ls.Length - 1 do
      Ls.[e] <- if a.[e - 1] then 0 else Ls.[e - 1] + 1
    let Rs = Array.create n 0
    for e in Rs.Length - 2.. -1..0 do
      Rs.[e] <- if a.[e + 1] then 0 else Rs.[e + 1] + 1
    let ord e = (min Ls.[e] Rs.[e], max Ls.[e] Rs.[e], -e)
    Seq.filter (fun e -> not a.[e]) {0..a.Length - 1}
     |> Seq.maxBy ord
     |> fun e ->
          a.[e] <- true
          ord e
  for e in 1..v - 1 do ignore (getNext())
  let b, a, _ = getNext()
  //printf "check: "
  sprintf "%i %i" a b  // |> debug
let case() =
  let [|n; v|] = ii()
  let rec f (k1, x1) (k2, x2) remainingV =
    //printfn "args: %A %A %A" (k1, x1) (k2, x2) remainingV
    // maintain k1 >= k2
    let split k x =
      if k % 2L = 0L
       then [k / 2L, x; k / 2L - 1L, x]
       else [(k - 1L) / 2L, x; (k - 1L) / 2L, x]
    let merge ll =
      List.sort ll
       |> List.fold (fun acc (k, x) ->
            match acc with
            |(k', x')::rest when k = k' -> (k, x + x')::rest
            |_ -> (k, x)::acc
           ) []
       |> function
            |[k1, x1; k2, x2] as yld -> yld
            |[k1, x1] -> [k1, x1; k1, 0L]
            |_ -> failwith "unexpected"
    split k1 x1 @ split k2 x2  // |> debug
     |> merge  // |> debug
     |> fun [k1', x1'; k2', x2'] ->
          let getAnswerPair k = split k 0 |> List.map fst |> fun [a; b] -> (a, b)
          if x1' >= remainingV then getAnswerPair k1'
          elif x1' + x2' >= remainingV then getAnswerPair k2'
          else f (k1', x1') (k2', x2') (remainingV - x1' - x2')
  let a, b =
    if v = 1L
     then if n % 2L = 0L then (n / 2L, n / 2L - 1L) else ((n - 1L) / 2L, (n - 1L) / 2L)
     else f (n, 1L) (n, 0L) (v - 1L)
  sprintf "%i %i" a b
  // |> debug
  // |> fun e -> if e = check (int n) (int v) then e else failwith "not correct"

for e in 1..int(i()) do
  printfn "%A" e
  pr.WriteLine(sprintf "Case #%i: %s" e (case()))
pr.Flush()

printfn "done"
inp.Close()
pr.Close()
let check'() =
    let inp = new StreamReader "input.txt"
    let ansinp = new StreamReader "output.txt"
    let i = inp.ReadLine
    let ii() = Array.map int (i().Split ' ')
    for e in 1..int(i()) do
      let ans = ansinp.ReadLine()
      let [|n; k|] = ii()
      let checked' = sprintf "Case #%i: %s" e (check n k)
      if checked' <> ans then
        printfn "incorrect #%i: %A in file, checked and got %A" e ans checked'
//try check'() with ex -> printfn "%A" ex
//printfn "done checking"
//stdin.ReadLine()