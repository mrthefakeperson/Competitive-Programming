
[<EntryPoint>]
let main(argv)=
 let m=int (System.Console.ReadLine())
 let mutable k=m
 //let mutable pr=[|for e in 0..m do yield true|]
 let mutable pr=(Array.init (m+1) (fun i->true))
 let mutable u=0
 let mutable count=0
 let DDo=
  let mutable me=true
  for e in 2..m/2 do
   if pr.[e] then
    count<-0
    while k%e=0 do
     k<-k/e
     count<-count+1
    if count>0 then
     printfn "%A^%A" e count
   if k=1 && me then
    printf "done"
    me<-false
    ()
   u<-e*2
   while u<=m do
    pr.[u]<-false
    u<-u+e
  0
(*
 let mutable count=0
 for e in 2..pr.Length-1 do
  if pr.[e] then
   count<-0
   //printfn "%A" e
   while k%e=0 do
    k<-k/e
    count<-count+1
   if count>0 then
    printfn "%A^%A" e count
*)
 ignore (System.Console.ReadLine())
 0