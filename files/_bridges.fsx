let q=System.Console.In.ReadLine()|>int
let bridges,pointer=Array.zeroCreate (q+5),ref 0
let total=ref -1L
let rec get n place jump=
 if place=0 then
  if bridges.[0]<n
   then 0
   else get n (jump) (if jump/2=0 then 1 else jump/2)
 elif place> !pointer then
  if bridges.[!pointer]>=n
   then !pointer+1
   else get n (!pointer+1-jump) (if jump/2=0 then 1 else jump/2)
 elif bridges.[place]<n && bridges.[place-1]>=n then
  place
 elif bridges.[place]>=n then
  get n (place+jump) (if jump/2=0 then 1 else jump/2)
 else
  get n (place-jump) (if jump/2=0 then 1 else jump/2)

for e in 1..q do
 let find=System.Console.In.ReadLine()|>int64
 let found,found1=
   get find 0 (!pointer/2),get (find+1L) 0 (if !pointer/2=0 then 1 else !pointer/2)
 if found1<>0 then total:= !total+1L
 total:= !total+int64(!pointer+1-get (find+1L) 0 (if !pointer/2=0 then 1 else !pointer/2))
 //printfn "%A;;  %A" (get (find+1L) 0 (if !pointer/2=0 then 1 else !pointer/2)) !pointer
 pointer:=found
 bridges.[found]<-find
 bridges.[found+1]<-0L
 //printfn "%A,%A" bridges total
System.Console.WriteLine(!total)



System.Console.ReadLine()