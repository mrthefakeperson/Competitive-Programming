open System.IO
open System.Collections.Generic

//let inp, pr = stdin, stdout
let inp, pr = new StreamReader "input.txt", new StreamWriter "output.txt"
let i = inp.ReadLine
let ii() = Array.map int (i().Split ' ')

let case() =
  let [|n; p|] = ii()
  let serving = ii()
  let data = Array.init n (fun _ -> ii())
  let getRange x servingSize =
    let l, r = (if x * 10 % 11 = 0 then x * 10 / 11 else x * 10 / 11 + 1), x * 10 / 9
    (if l % servingSize = 0 then l / servingSize else l / servingSize + 1), r / servingSize
  let ranges =
    Array.mapi (fun i ->
      Array.map (fun e ->
        let a, b = getRange e serving.[i]
        a, b, i
       )
     ) data
     |> Array.concat
     |> Array.filter (fun (l, r, _) -> l <= r)
     |> Array.sort
  //printfn "ranges: %A" ranges
  let packages = Array.init n (fun _ -> ResizeArray(), 0)
  //printfn "%A" packages
  let append pIndex e = (fst packages.[pIndex]).Add e
  let front pIndex =
    let a, b = packages.[pIndex]
    if b < a.Count then Some a.[b]
    else None
  let popFront pIndex =
    let a, b = packages.[pIndex]
    packages.[pIndex] <- a, b + 1

  let acc = ref 0
  Array.iter (fun (l, r, pIndex) ->
    append pIndex (l, r)
    for e in 0..n - 1 do
      let shouldPop() =
        match front e with
        |Some(ll, rr) when rr < l -> true
        |_ -> false
      while shouldPop() do popFront e
    while
      Seq.forall (fun e -> match front e with Some _ -> true | None -> false) {0..n - 1}
     do
      for e in 0..n - 1 do popFront e
      incr acc
   ) ranges
  sprintf "%i" !acc

for e in 1..int(i()) do
  printfn "%A" e
  try pr.WriteLine(sprintf "Case #%i: %s" e (case()))
  with
   ex ->
    printfn "%A" ex
    ignore (stdin.ReadLine())
pr.Flush()