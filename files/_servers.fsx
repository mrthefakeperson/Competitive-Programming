open System.Collections.Generic
open System.IO
let visited=Dictionary<int,int>()
let inp=StreamReader(System.Console.OpenStandardInput())
let peeps,cases=match inp.ReadLine().Split(' ') with |[|a;b|]->(int a,int b)
//let r=Array.init peeps (fun e->(2.**float(e))|>int)
let r=[|1;2;4;8;16;32;64;128;256;512;1024;2048;4096;8192;16384;32768;65536;131072;262144;524288|]
let sets,goal=Array.init cases (fun e->[]),Array.sum r.[0..peeps-1]
let st=ref 0
let pass=String.init cases (fun _->"O")
for person in 0..peeps-1 do
 let m=inp.ReadLine()
 if m=pass then st:=r.[person]+ !st
 for e in 0..cases-1 do
  if m.[e]='X' then sets.[e]<-person::sets.[e]
let picked=Array.zeroCreate peeps
let rec pick n hash depth=                     //pick set no. n
 let nxt=ref 0
 List.iter (fun e->
  picked.[e]<-picked.[e]+1
  if picked.[e]=1 then nxt:= !nxt+r.[e]
 ) sets.[n]
 let rr=
  match hash+ !nxt with
  |a when a=goal->(1,[n])
  |a when visited.ContainsKey(a) && visited.[a]<=depth->(1000000,[])
   //visited.[a]
  |a->
   let mm=ref (1000000,[])
   for e in cases-1..-1..n+1 do
    let value,taken=pick e a (depth+1)
    if value<fst !mm then mm:=(value,taken)
   //visited.[a]<-(fst !mm+1,n::snd !mm)
   visited.[a]<-depth
   (fst !mm+1,n::snd !mm)
 List.iter (fun e->picked.[e]<-picked.[e]-1) sets.[n]
 rr
let mm=ref (1000000,[])
for e in cases-1..-1..0 do
 let value,taken=pick e !st 1
 if value<fst !mm then mm:=(value,taken)
let outt=StreamWriter(System.Console.OpenStandardOutput())
outt.WriteLine(fst !mm)
List.iter (fun (e:int)->outt.Write(e+1);outt.Write(' ')) (snd !mm)
outt.Flush()
//List.concat (List.map (fun e->sets.[e]) (snd !mm))|>List.sort|>printfn "%A"


System.Console.ReadLine()