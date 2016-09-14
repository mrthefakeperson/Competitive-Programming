type node(value:int)=
 let s=value
 let mutable connected:node list=(if s= -1 then [] else [new node(-1);new node(-1)])
 let mutable size=(if s= -1 then 0 else 1)
 member obj.stored=s
 member obj.count=size
 member obj.push (n:node) (ind:int)=
   size<-size+1
   if n.stored>=obj.stored then
    if (connected.[0]).stored= -1 then
     connected<-[n;connected.[1]]
     ind
    else
     (connected.[0]).push n ind
   else
    if (connected.[1]).stored= -1 then
     connected<-[connected.[0];n]
     ind+1+(connected.[0]).count
    else
     (connected.[1]).push n (ind+1+(connected.[0]).count)

let __=System.Console.In.ReadLine()|>int
//let ss=new node(1)
let sourceNode=new node(System.Console.In.ReadLine()|>int)
let mutable track:int64=1L
for e in 2..__ do
 let sc=System.Console.In.ReadLine()|>int
 let pp=sourceNode.push (new node(sc)) 0
 //printfn "%A out of %A" (pp+1) e
 track<-track+(int64 pp)+1L
 if e%1000=0 then
  ()

let outt=
 let rr=System.Math.Round((float track)/(float __),2)|>string
 if not (rr.Contains ".") then (rr+".00")
 elif ((rr.Length-1-rr.IndexOf '.')=1) then rr+"0"
 else rr
System.Console.Out.WriteLine(outt)


System.Console.ReadLine()