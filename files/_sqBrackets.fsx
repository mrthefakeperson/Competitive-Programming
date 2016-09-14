open System
//let n,k,L=int (Console.ReadLine()),int (Console.ReadLine()), (Console.ReadLine()).Split [|' '|]
let mutable n,L=0,[||]
let solve()=
 let mutable map=Array2D.init n n (fun x y->if x-y>=2 then -1 else 0)
 map.[n-1,n-1]<-1
 //printfn "%A" map
 map
let getNext last (map:int[,])=
 let m=ref true
 let mutable k=[for e in last do
                 if !m then
                  m:=false
                  if (snd e)-1>=0 then
                   yield (fst e,(snd e)-1)
                 if (fst e)-1>=0 then
                  //if map.[(fst e)-1,snd e] <> -1 then
                  yield ((fst e)-1,snd e)]
 //printfn "K: %A" k
 k
let stuff()=
 let mutable map=solve()
 let me=ref [(n-1,n-1)]
 let mutable fl=n*2-1
 while not(List.exists ((=)(0,0)) !me) do
  fl<-fl-1
  me:=getNext !me map
  for e in !me do
   if (snd e)+1<n then
    if map.[fst e,(snd e)+1] <> -1 && map.[fst e,snd e] <> -1 then
     map.[fst e,snd e]<-map.[fst e,snd e]+map.[fst e,(snd e)+1]
   if not (Array.exists ((=)((fl+1).ToString())) L) then
    if (fst e)+1<n then
     if map.[(fst e)+1,snd e] <> -1 && map.[fst e,snd e] <> -1 then
      map.[fst e,snd e]<-map.[fst e,snd e]+map.[(fst e)+1,snd e]
 //map |> printfn "%A"
 map.[0,0] |> printfn "%A"

let main argv=
 let kk=int (Console.ReadLine())
 for e in 1..kk do
  n<-int (Console.ReadLine().Split [|' '|]).[0]
  L<-Console.ReadLine().Split [|' '|]
  if Array.exists ((=)((2*n).ToString())) L then printfn "%A" 0
  else
   stuff()
 //Console.ReadLine() |> ignore
main [||]