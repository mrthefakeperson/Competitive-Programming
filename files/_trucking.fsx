open System.IO
let inp=StreamReader(System.Console.OpenStandardInput())
let cities,roads,destinations=
 match inp.ReadLine().Split(' ') with
 |[|a;b;c|]->
  (int a,int b,int c)
let disjoint=Array.init (cities+1) (fun e->e)
let rec unravel x=
 if disjoint.[x]=x
  then x
  else
   disjoint.[x]<-unravel disjoint.[x]
   disjoint.[x]

let allRoads=
 (List.init roads (fun e->
  match inp.ReadLine().Split(' ') with
  |[|a;b;c|]->
   ((int a,int b),int c)
 )) |> (List.sortBy (fun e-> -(snd e)))
let allDests=(List.init destinations (fun e->inp.ReadLine()|>int))

let rec applyRoads ll=
 match ll with
 |hd::tl->
  let a,b=fst hd
  let _=unravel a,unravel b
  let aa,bb=disjoint.[a],disjoint.[b]
  if aa<>bb
   then
    if aa<bb
     then disjoint.[bb]<-aa
     else disjoint.[aa]<-bb
  //printfn "%A %A" disjoint hd
    if disjoint.[aa]=1
     then
      if List.forall (fun e->
       unravel e=1) allDests
       then snd hd
       else applyRoads tl
     else applyRoads tl
   else applyRoads tl

System.Console.Out.WriteLine(applyRoads allRoads)



System.Console.ReadLine()