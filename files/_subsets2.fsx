let rec ( ** ) a=function
|0->1
|b->a*(a**(b-1))
let pow=Array.init 12 (fun e->2**e |> int)
let convert nn e=
 nn&&&pow.[e]=0 |> not

let check a b=
 let mutable rr=true
 for e in 0..9 do
  if convert a e then
   if convert b e || convert b (e+1) then
    rr<-false
 rr
//while true do printfn "%A" (check (System.Console.ReadLine() |> int) (System.Console.ReadLine() |> int))

let rec HELP max lowest (vv:int[]) ps=
 //printfn "%A" vv
 let low=lowest*2
 let rec count n=
  if n>max then 0
  elif n%2=1 then 1
  else 1+(count (3*n/2))
 let size=count low
 let ss=2**size
 let nv=Array.zeroCreate ss
 
 for e in 0..ps-1 do
  for ee in 0..ss-1 do
   if check e ee then       //the slow part
    nv.[ee]<-(nv.[ee]+vv.[e])%1000000001

 if size=0
  then Array.fold (fun acc e->(acc+e)%1000000001) 0 vv
  else HELP max (lowest*2) nv ss
let n=System.Console.ReadLine() |> int
let thing=Array.init (n+1) id
let collect=Array.create (n+1) 0
for e in 2..n do
 if e%2=0 then
  thing.[e]<-thing.[e/2]
 elif e%3=0 then
  thing.[e]<-thing.[e/3]
 collect.[thing.[e]]<-e/thing.[e]
collect.[0]<-0
let visited=Array.zeroCreate (n+1)
Array.fold (fun acc->function
 |0->acc
 |e->
  //printfn "%A" e
  if visited.[e]=0 then
   let res=HELP e 1 [|1;1|] 2
   visited.[e]<-res
   (int64 res*acc)%1000000001L
  else (int64 visited.[e]*acc)%1000000001L
) 1L collect
 |> System.Console.Out.Write


System.Console.ReadLine()