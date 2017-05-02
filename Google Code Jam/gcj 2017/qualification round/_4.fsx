open System.IO

//let inp, pr = stdin, stdout
let inp, pr = new StreamReader "input.txt", new StreamWriter "output.txt"
let i = inp.ReadLine
let ii() = Array.map int (i().Split ' ')
let debug e = printfn "debug: %A" e; e

type Edge = Edge of char*row:int*col:int*nodeA:int*nodeB:int
let getGridValue = function Edge(c, rr, cc, _, _) -> (c, rr, cc)
let getEdge = function Edge(_, _, _, a, b) -> (a, b)
let case() =
  let maximumMatching size edges =
    //printfn "Edges: %A" edges
    let adjLeft = Array.create size []
    List.iter (fun e ->
      let a, b = getEdge e
      adjLeft.[a] <- b::adjLeft.[a]
     ) edges
    let occupiedRight = Array.create size None
    let rec findPath (visitedL:bool[], visitedR:bool[]) leftNode =
      visitedL.[leftNode] <- true
      let rightNodes =
        List.filter (fun e -> not visitedR.[e]) adjLeft.[leftNode]
      List.iter (fun e -> visitedR.[e] <- true) rightNodes
      let leftNodes' =
        List.map (fun e ->
          match occupiedRight.[e] with Some l -> Choice1Of2 (l, e)
                                     | None -> Choice2Of2 e) rightNodes
      match List.tryFind (function Choice2Of2 x -> true | _ -> false) leftNodes' with
      |Some(Choice2Of2 unoccupiedRightNode) -> Some [leftNode; unoccupiedRightNode]
      |_ ->
        let leftNodes' =
          List.map
           (function Choice1Of2 (leftNode', r) -> leftNode', r | _ -> failwith "should never happen")
           leftNodes'
           |> List.filter (fun (e, _) -> not visitedL.[e])
        List.fold (fun ans (leftNode', r) ->
          match ans with
          |Some _ -> ans
          |None ->
            match findPath (visitedL, visitedR) leftNode' with
            |Some ll -> Some (leftNode::r::ll)
            |None -> None
         ) None leftNodes'
    let pushPath size leftNode =
      match findPath (Array.create size false, Array.create size false) leftNode with
      |Some ll ->
        //printfn "from %A, found %A" leftNode ll
        let rec applyPath = function
          |leftA::right::rest ->
            occupiedRight.[right] <- Some leftA
            applyPath rest
          |[] -> ()     |[_] -> failwith "odd number of nodes found in path???"
        applyPath ll
      |None -> ()
    let gridValueFromEdge =
      List.map (fun e -> getEdge e, getGridValue e) edges
       |> dict
    for e in 0..size - 1 do pushPath size e
    //printfn "right matchings: %A" occupiedRight
    Array.mapi (fun rightNode -> function
      |Some leftNode ->
        Some gridValueFromEdge.[(leftNode, rightNode)]
      |None -> None
     ) occupiedRight
     |> Array.choose id
     |> Array.toList

  let solve() =
    let [|n; m|] = ii()
    let grid = Array2D.create n n '.'
    for e in 1..m do
      let [|c; rr; cc|] = i().Split ' '
      let c, rr, cc = char c, int rr - 1, int cc - 1
      grid.[rr, cc] <- c
    let row, column, diag1, diag2 = Array.create n [], Array.create n [], Array.create (2*n) [], Array.create (2*n) []
    for r in 0..n-1 do
      for c in 0..n-1 do
        let d1, d2 = r + c, r - c + n-1
        row.[r] <- (r, c)::row.[r]
        column.[c] <- (r, c)::column.[c]
        diag1.[d1] <- (r, c)::diag1.[d1]
        diag2.[d2] <- (r, c)::diag2.[d2]
    //printfn "%A\n%A" diag1 diag2
    let edges = [
      for r in 0..n-1 do
        for c in 0..n-1 do
          let d1, d2 = (r + c, r - c + n-1)
          //printfn "r, c: %A" (r, c)
          let ``no+conflict`` =
            List.filter ((<>) (r, c)) (row.[r] @ column.[c])       // |> debug
             |> List.forall (fun (x, y) -> grid.[x, y] = '.' || grid.[x, y] = '+')
          if ``no+conflict`` && grid.[r, c] <> 'x' && grid.[r, c] <> 'o' then yield Edge('x', r, c, r, c)
          let noxconflict =
            List.filter ((<>) (r, c)) (diag1.[d1] @ diag2.[d2])       // |> debug
             |> List.forall (fun (x, y) -> grid.[x, y] = '.' || grid.[x, y] = 'x')
          if noxconflict && grid.[r, c] <> '+' && grid.[r, c] <> 'o' then yield Edge('+', r, c, d1, d2)
     ]
    //printfn "edges: %A" edges
    let edgesRC, edgesDiag = List.partition (function Edge('x', _, _, _, _) -> true | _ -> false) edges
    let answer = maximumMatching n edgesRC @ maximumMatching (2*n) edgesDiag
    let answerSteps =
      List.map (function      // in case of '.' -> 'o', this will do '.' -> ('+' | 'x') -> 'o'
        |'+', r, c ->
          let c' = match grid.[r, c] with '.' -> '+' | 'x' -> 'o' | _ -> failwith "invalid placement"
          grid.[r, c] <- c'
          (c', r + 1, c + 1)
        |'x', r, c ->
          let c' = match grid.[r, c] with '.' -> 'x' | '+' -> 'o' | _ -> failwith "invalid placement"
          grid.[r, c] <- c'
          (c', r + 1, c + 1)
       ) answer
    let answerSteps =
      let oGrid = Array2D.create (n+1) (n+1) false
      List.iter (function
        |'o', r, c -> oGrid.[r, c] <- true
        |_ -> ()
       ) answerSteps
      List.filter (function 'o', _, _ -> true | _, r, c -> not oGrid.[r, c]) answerSteps
       |> List.map (fun (c, rr, cc) -> sprintf "%c %i %i" c rr cc)
    //printfn "%A" grid
    let totalPoints =
      let yld = ref 0
      Array2D.iter (function 'o' -> yld := !yld + 2 | '+' | 'x' -> incr yld | '.' -> ()) grid
      !yld
    let procedureLength = List.length answerSteps
    sprintf " %i %i" totalPoints procedureLength :: answerSteps

  solve()

for e in 1..int(i()) do
  printfn "%A" e
  let ansList = case()
  pr.Write(sprintf "Case #%i: " e)
  List.iter (pr.WriteLine:string -> unit) ansList
pr.Flush()