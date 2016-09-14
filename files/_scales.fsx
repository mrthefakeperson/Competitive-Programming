open System.IO
let inp=new StreamReader(System.Console.OpenStandardInput())
let i()=inp.ReadLine().Split(' ') |> Array.map int
let width,height,area=
 match i() with
 |[|a;b;c|]->(a,b,c)

let field=Array.init height (fun e->i())
let otherThing=Array.init (height+1) (fun e->Array.zeroCreate (width+1))
otherThing.[height].[width]<-0
for e in 1..height do
 for ee in 1..width do
  otherThing.[e].[ee]<-field.[e-1].[ee-1]-otherThing.[e-1].[ee-1]+otherThing.[e-1].[ee]+otherThing.[e].[ee-1]
//printfn "%A" otherThing
//let factorPairs=List.init (System.Math.Sqrt(float area) |> int) (fun e->(e,area/e))
let get a b=
 let x=if a<0 then 0 else a
 let y=if b<0 then 0 else b
 otherThing.[x].[y]
let sq=System.Math.Sqrt(float area) |> int
let maxx=ref 0
Array.iteri (fun i e->
 Array.iteri (fun ii ee->
  for e in 1..sq do
   let x,y=e,area/e
   let nnn=
    max (ee+get (i-x) (ii-y)-get i (ii-y)-get (i-x) ii) (ee+get (i-y) (ii-x)-get i (ii-x)-get (i-y) ii)
   maxx:=max !maxx nnn
 ) e
) otherThing

System.Console.Write !maxx



System.Console.ReadLine()