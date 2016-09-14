open System.IO
let inp=new StreamReader(System.Console.OpenStandardInput())
let n,m=match (inp.ReadLine().Split [|' '|]) with
        |[|a;b|]->(int a,int b)
let board:bool[][]=Array.init (n+1) (fun e->Array.zeroCreate (n+1))
for e_ in 1..m do
 match Array.map int (inp.ReadLine().Split [|' '|]) with
 |[|x;y;w;h|]->
  board.[x].[y]<-not board.[x].[y]
  board.[x+w].[y]<-not board.[x+w].[y]
  board.[x].[y+h]<-not board.[x].[y+h]
  board.[x+w].[y+h]<-not board.[x+w].[y+h]

//printfn "%A" board

let column:bool[]=Array.zeroCreate (n+1)
let mutable final=0
Array.iteri (fun ii thisColumn->
 let sum,flip=ref 0,ref false
 Array.iteri2 (fun i e1 e2->
  if e2 then
   if not e1 then
    flip:=not !flip
   column.[i]<-not column.[i]
  elif e1 then flip:=not !flip
  if !flip then
   //printfn "%A,%A" ii i 
   sum:=1+ !sum
 ) column thisColumn
 //printfn "%A" column
 final<-final+ !sum
) board
System.Console.Out.WriteLine(final)

System.Console.ReadLine()