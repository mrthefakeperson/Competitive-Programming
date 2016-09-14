//it is faster to fold many short arrays than it is to fold a few long arrays

open System.IO
let inp=StreamReader(System.Console.OpenStandardInput())
//let y,x,k=inp.ReadLine()|>int,inp.ReadLine()|>int,inp.ReadLine()|>int
let x,y,k=inp.ReadLine()|>int,inp.ReadLine()|>int,inp.ReadLine()|>int
//indexed by everywhere.[y].[x]
let everywhere=Array.init y (fun e->
 Array.zeroCreate (x+1):int[]
)
for e_ in 1..k do
 match inp.ReadLine().Split(' ') with
 |[|aa;ba;ca;da|]->
  //let xx,yy,rad,value=int aa-1,int ba-1,int ca,int da
  let yy,xx,rad,value=int aa-1,int ba-1,int ca,int da
  for e in -rad..rad do
   if yy+e>=0 && yy+e<y then
    let xOffset=System.Math.Sqrt(float(rad*rad-e*e))|>int
    let mn,mx=System.Math.Max(0,xx-xOffset),System.Math.Min(x,xx+xOffset+1)
    if mx>=0 && mn<=x then
     //let mn,mx=System.Math.Max(0,xx-xOffset),System.Math.Min(x,xx+xOffset+1)
     everywhere.[yy+e].[mn]<-everywhere.[yy+e].[mn]+value
     everywhere.[yy+e].[mx]<-everywhere.[yy+e].[mx]-value

let maxSoFar,amtOfMax=ref 0,ref 0
//got the 1D diff array
//printfn "%A" everywhere
Array.iter (fun ee->
 Array.fold (fun acc e->
  let qq=acc+e
  if qq> !maxSoFar then
   maxSoFar:=qq
   amtOfMax:=1
  elif qq= !maxSoFar then amtOfMax:= !amtOfMax+1
  qq
 ) 0 ee|>ignore
) everywhere
//let outt=StreamWriter(System.Console.OpenStandardOutput())
System.Console.Out.WriteLine(!maxSoFar);System.Console.Out.Write(!amtOfMax)
//outt.WriteLine(!maxSoFar);outt.Write(!amtOfMax)
//outt.Flush()


System.Console.ReadLine()