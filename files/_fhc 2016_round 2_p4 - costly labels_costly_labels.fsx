#load "matchme.fsx"
open System
open System.IO

let inp = new StreamReader "input.txt"
let pr  = new StreamWriter "output.txt"

let oneCase()=
 let ii()=Array.map int (inp.ReadLine().Split ' ')
 match ii() with
  [|n;k;p'|]->
   let p=int64 p'
   let costs=Array.append [|Array.create k 0L|] (Array.init n (fun _->Array.map int64 <| ii()))
   let adj=Array.init (n+1) (fun _->[])
   for e in 2..n do
    match ii() with
     [|a;b|]->
      adj.[a]<-b::adj.[a]
      adj.[b]<-a::adj.[b]

   //given a list of label matching costs, returns a list of optimal prices
   let solve=function
     |[||]->Array.create k 0L
     |matching->
       //printfn "%A \n  %A" parentMatching matching
       let greedy=p + Array.sumBy Array.min matching
       if matching.Length>=k
        then Array.create k greedy
        else
          let highest=matching |> Array.map Array.max |> Array.max
          let st=
            let parentRow=Array.create k 9999999999999999L
            Array.concat [|[|parentRow|];matching;Array.init (k-matching.Length-1) (fun _->Array.create k highest)|]
          {0..k-1}
           |> Seq.map (fun e->
                st.[0].[e]<-0L
                if e<>0 then st.[0].[e-1]<-9999999999999999L
                st
                 |> Matching.solve
                // |> fun e->printfn "%A" e;e
                 |> fun solvedCosts->Array.sum solvedCosts.[..matching.Length]
                 |> min greedy
               )
           |> Array.ofSeq
   //returns the full list of prices for each label
   let rec search (visited:bool[]) node=
     visited.[node]<-true
     let twoAway,oneAway=
       adj.[node]
        |> List.filter (fun e->not visited.[e])
        |> List.map (search visited)
        |> List.unzip
     let matchSelf=
       List.fold (fun acc e->
         Array.zip acc e |> Array.map (fun (a,b)->a+b)
        ) costs.[node] twoAway
     let matchUnder=
       solve (Array.ofList oneAway)

     //printfn "node %A: %A -> %A" node (twoAway,oneAway) (matchUnder,matchSelf)
     (matchUnder,matchSelf) //matching nodes directly under this one, matching this node

   let a=search (Array.create (n+1) false) 1 |> snd |> Array.min
   let b=if n=1 then 0L else search (Array.create (n+1) false) adj.[1].Head |> snd |> Array.min
   a+b




for e in 1..inp.ReadLine() |> int do
 printfn "%A.." e
 try pr.WriteLine (sprintf "Case #%A: %O" e (oneCase()))
 with
 |ex->printfn "%A" ex

pr.Flush()
pr.Close()
Console.ReadLine()