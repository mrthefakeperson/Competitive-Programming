let sve (lll:int list)=
 let mutable ll=lll
 let (pr:bool[])=Array.zeroCreate (ll.[0]*(ll.[0]-1))
 let shift=ll.[0]+1
 for e in ll do
 
  for num in e*int(ceil(float(shift)/float(e)))..e..ll.[0]*ll.[0] do
   //printf"%A,%A " num e
   pr.[num-shift]<-true
 for e in 0..pr.Length-1 do
  if not pr.[e] then ll<-e+shift::ll
 ll
let targ=System.Console.ReadLine()|>int
let start=System.Environment.TickCount
let mutable kk=[2]
while kk.[0]<targ do
 kk<-sve kk
printfn "%A; %A elements; last:%A" (System.Environment.TickCount-start) kk.Length kk.[0]
//for e in kk do
 //printfn "%A" e
System.Console.ReadLine()