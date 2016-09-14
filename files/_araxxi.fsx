(*
open System

let ii()=Array.map int (stdin.ReadLine().Split ' ')
match ii() with
|[|n;m|]->
  let attacks,techniqueCosts=ii() |> Array.map ((+) -1),ii() |> Array.map ((+) 1)
  let cost e=techniqueCosts.[e]
  let lastUse,minMaxSuffix=Array.create (m+1) 0,Array.create (n+1) 0
  for e in n-1.. -1..0 do
    let atk=attacks.[e]
    lastUse.[atk]<-1 + max minMaxSuffix.[min n (e+cost atk)] lastUse.[atk]
    minMaxSuffix.[e]<-max lastUse.[atk] minMaxSuffix.[e+1]
  stdout.WriteLine minMaxSuffix.[0]
  *)

(fun [|n;m|] (attacks:int[]) (techniqueCosts:int[])->Seq.fold (fun (lastUse:int[],minMaxSuffix:int[]) e->(lastUse.[attacks.[e]]<-1 + max minMaxSuffix.[min n (e+techniqueCosts.[attacks.[e]])] lastUse.[attacks.[e]]) |> (fun()->minMaxSuffix.[e]<-max lastUse.[attacks.[e]] minMaxSuffix.[e+1]) |> (fun()->(lastUse,minMaxSuffix))) ((Array.create (m+1) 0),(Array.create (n+1) 0)) {n-1.. -1..0}) (Array.map int (stdin.ReadLine().Split ' ')) (Array.map ((+) -1) (Array.map int (stdin.ReadLine().Split ' '))) (Array.map ((+) 1) (Array.map int (stdin.ReadLine().Split ' '))) |> fun (_,e)->stdout.WriteLine e.[0]