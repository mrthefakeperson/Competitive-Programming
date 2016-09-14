open System.IO
let inp=new StreamReader(System.Console.OpenStandardInput())
let nn=inp.ReadLine()|>int
let n=
 let mutable qq=1
 while qq<nn do qq<-qq*2
 qq
let bins=Array.map int (inp.ReadLine().Split(' '))
let overhead=Array.create (n*2) 0
let minStored=Array.create (n*2) 100001

let rec siftUp p=
 if p<>0 then
  minStored.[p]<-overhead.[p]+System.Math.Min(minStored.[p*2],minStored.[p*2+1])
  siftUp (p/2)
let rec update item inc place value jump=
 if jump=0
  then
   //minStored.[place]<-overhead.[place]
   siftUp (place/2)
  else
   if item>=value+jump
    then
     //overhead.[place*2]<-overhead.[place*2]+inc
     //minStored.[place*2]<-minStored.[place*2]+inc
     update item inc (place*2+1) (value+jump) (jump/2)
    else
     overhead.[place*2+1]<-overhead.[place*2+1]+inc
     minStored.[place*2+1]<-minStored.[place*2+1]+inc
     update item inc (place*2) value (jump/2)
     (*
let update_ a b c d e=
 if a=n
  then
   overhead.[1]<-overhead.[1]+b
   minStored.[1]<-minStored.[1]+b
  else update a b c d e
  *)
let mutable minSoFar=0
for mm in 1..nn/2 do
 update (bins.[mm*2-1]) 1 1 1 (n/2)
 update (bins.[mm*2-2]) 1 1 1 (n/2)
 minStored.[n-1+bins.[mm-1]]<-0+overhead.[n-1+bins.[mm-1]]
 update (bins.[mm-1]) (-2) 1 1 (n/2)
 siftUp ((bins.[mm-1]+nn-1)/2)
 if minStored.[1]>0 then minSoFar<-mm
 //printfn "%A right->left;; %A and %A added to right" bins.[mm-1] bins.[mm*2-1] bins.[mm*2-2]
 //printfn "%A\n%A" minStored overhead
System.Console.Out.WriteLine(minSoFar)



System.Console.ReadLine()