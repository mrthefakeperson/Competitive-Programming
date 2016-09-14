let thing=System.Console.ReadLine().Split(' ') |> Array.map int
let total,amt=thing.[0],thing.[1]

let HELP n=
 let rr=2*(n/amt+1)
 if n%amt=0 then rr-1 else rr

let mutable acc=0L
let sieve=Array.zeroCreate (total+1)
for e in 2..total do
 if not sieve.[e] then
  for ee in e..e..total do
   sieve.[ee]<-true
  acc<-acc+int64(HELP (total-e))
System.Console.Write acc


System.Console.ReadLine()