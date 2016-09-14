open System.IO
open System

let inp = new StreamReader("input.txt")
let pr = new StreamWriter("output.txt")

(*
  read a bunch of strings,
  sort them,
  find largest prefix between adjacent strings,
  find all pairs' largest common prefix using dynamic programming,
    for each x and y, what is the minimum of all adjacent pairs from x to y (in sorted order)?
  get the shortest edit distance for all pairs by mapping largest prefix to sum of lengths less twice that of largest prefix,
  find best case of starting and ending with "" using dynamic programming
    for each x and y, what is the shortest edit path going strictly left toward x, ending at x, and taking y strings?
*)
let oneCase()=
 let n,k=inp.ReadLine().Split ' ' |> Array.map int |> function [|a;b|]->(a,b) |_->(9999,9999)
 let strings=Array.init n (fun _->inp.ReadLine()) |> Array.append <| [|""|]   //put the empty string there
 Array.sortInPlace strings
 let largestPrefix=Array2D.zeroCreate (n+1) (n+1)
 let findPrefix (a:string) (b:string)=
  let rec ff e=
   if e>=a.Length || e>=b.Length
    then e
    else
     if a.[e]<>b.[e]
      then e
      else ff (e+1)
  ff 0
 //remember, the strings array is (n+1) long due to the empty string and ends at index n
 for e in 0..n-1 do
  largestPrefix.[e,e+1]<-findPrefix strings.[e] strings.[e+1]
 for e in 0..n-1 do
  for ee in e+2..n do
   largestPrefix.[e,ee]<-min largestPrefix.[ee-1,ee] largestPrefix.[e,ee-1]
 let editDistance=
  Array2D.mapi (fun x y e->
   if x>=y
    then 0
    else
     strings.[x].Length+strings.[y].Length-2*e
  ) largestPrefix

 let visited=Array2D.create (n+1) (k+1) -1
 let mmmkay=Array2D.create (n+1) (k+1) -1        //
 let rec answer x y=
  if visited.[x,y]= -1 then
   visited.[x,y]<-
    if y=1
     then editDistance.[0,x]   //x should never be 0
     else
        {y-1..x-1}
         |> Seq.minBy (fun e->answer e (y-1) + editDistance.[e,x])
         |> fun e->
             mmmkay.[x,y]<-e
             answer e (y-1) + editDistance.[e,x]
  visited.[x,y]
 {k..n}
  |> Seq.minBy (fun e->answer e k + editDistance.[0,e])
  |> fun e->answer e k + editDistance.[0,e]
  |> (+) k
  |> pr.WriteLine
 
 printfn "%A" mmmkay

for e in 1..inp.ReadLine() |> int do
 pr.Write "Case #"
 pr.Write e
 pr.Write ": "
 try
  oneCase()
 with
 |e->printfn "%A" e
 printfn "%A" e
 Console.ReadLine() |> ignore
pr.Flush()
inp.Close()
pr.Close()