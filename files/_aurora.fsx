let i()=System.Console.In.ReadLine().Split(' ')
let soldiers,stations=
 match i() with
 |[|n;m|]->int64 n,int64 m
let a,b,c=
 match i() with
 |[|aa;bb;cc|]->bigint(int64 aa),bigint(int64 bb),bigint(int64 cc)
let allSoldiers=i()|>Array.map (fun e->bigint(int64 e))|>Array.sort|>Array.rev//|>Array.map (fun e->e*b-b)
let auroraSoldiers=ref 0
try
 Array.map (fun e->
   let oldTime=e*b-b
   let newTime=(e-1I)*a+c* bigint(!auroraSoldiers)
   if newTime<oldTime
    then
     auroraSoldiers:= !auroraSoldiers+1
     newTime
    else oldTime
  ) allSoldiers|>Array.fold (fun acc e->acc+e) 0I|>System.Console.Out.Write
with
|e->System.Console.Write e




i()
