open System.IO
let inp=new StreamReader(System.Console.OpenStandardInput())
let addresses=List.init (inp.ReadLine()|>int) (fun e->inp.ReadLine()|>int)|>List.sort
let maxx=(List.rev addresses).[0]
let hydrants=inp.ReadLine()|>int
let rec tryHose lngth ll prevSource=
 match ll with
 |hd::tl->
  if hd-prevSource<=lngth then
   tryHose lngth tl prevSource
  else
   (tryHose lngth tl hd)+1
 |[]->1
let rec attemptHose lngth ll=
 if tryHose (lngth*2) ll (ll.[0])<=hydrants then
  //printfn "%A" ll
  true
 else
  match ll with
  |hd::tl when hd-1000000>maxx->
   //printfn "%A" hd
   false
  |hd::tl->
   attemptHose lngth (tl@[hd+1000000])

//printfn "%A" (attemptHose 10000 addresses)

let attempt=1000000/hydrants/2
let rec findd attmptLngth jump=
 match jump with
 |1->attmptLngth
 |_ when attemptHose attmptLngth addresses->findd (attmptLngth-jump) (jump/2)
 |_->findd (attmptLngth+jump) (jump/2)
let fsts=findd attempt (attempt/2)

let rec find=function
|q when attemptHose q addresses->q
|q->find (q+1)
let rec find2=function
|q when not(attemptHose q addresses)->q+1
|q->find2 (q-1)
if addresses.Length<=hydrants then System.Console.Out.WriteLine(0)
else System.Console.Out.WriteLine(fsts|>find|>find2)

System.Console.ReadLine()