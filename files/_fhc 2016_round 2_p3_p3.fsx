open System
open System.IO

let inp = new StreamReader "input.txt"
let pr = new StreamWriter "output.txt"


let oneCase() =
 let n=inp.ReadLine() |> int
 let snakes=
  List.init n (fun _->match inp.ReadLine().Split ' ' with [|a;b|]->(int a,int b))
   |> List.sort
   |> List.map (fun (a,b)->(b,a))
 //highest to lowest
 let hull=Array.create n (0,[])
 let pt=ref 0
 let find good x ll bd=
  let mutable place,jump= -1,bd
  while jump>0 do
   if good (place+jump) x ll bd then place<-place+jump
   jump<-jump/2
  while good (place+1) x ll bd do place<-place+1
  place+1
 let after place x (ll:(int*int list)[]) bd=
  if place>=bd
   then false
   else fst ll.[place]>x
 let addToHull x=
  find after x hull !pt

 let getSum ll=
 // printfn "%A" ll
  let sq=List.sumBy (fun (e:int)->bigint(e)*bigint e) ll
  List.fold (fun (acc,preSum) (e:int)->
   (acc-2I*preSum*bigint e,preSum+bigint e)
  ) ((bigint(List.length ll)-1I)*sq,0I) ll
   |> fst
 let cnt=ref 0I
 List.iter (fun (h,xx)->
  let pl=addToHull h
  //cnt:= !cnt+({pl.. !pt-1} |> Seq.sumBy (fun e->getSum (snd hull.[e])))
  hull.[pl]<-
   if fst hull.[pl]<>h || pl= !pt
    then
     cnt:= !cnt+({pl.. !pt-1} |> Seq.sumBy (fun e->getSum (snd hull.[e]|>List.rev)))
     (h,[xx])
    else
     cnt:= (!cnt+({pl+1.. !pt-1} |> Seq.sumBy (fun e->getSum (snd hull.[e]|>List.rev))))
     (h,xx::snd hull.[pl])
  pt:=pl+1
//  printfn "%A, %A" !pt hull
 ) snakes
 cnt:= (!cnt+({0.. !pt-1} |> Seq.sumBy (fun e->getSum (snd hull.[e]|>List.rev))))
 !cnt%1000000007I
     

for e in 1..inp.ReadLine() |> int do
 printfn "%A" e
 pr.Write "Case #"
 pr.Write e
 pr.Write ": "
 try
  oneCase() |> pr.WriteLine
 with
 |e->
  printfn "%A" e
  Console.ReadLine() |> ignore

pr.Flush()
pr.Close()
Console.ReadLine()