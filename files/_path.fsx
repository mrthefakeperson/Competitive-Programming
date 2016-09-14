let input()=System.Console.In.ReadLine().Split [|' '|]|>(Array.map int)
let kk=input()
let totalHull,paths,m=kk.[0],Array.init (kk.[1]+1) (fun e->[]),kk.[2]
for e in 1..m do
 let kk=input()
     //paths[source]: list of: (destination,(time,hull_damage))
 paths.[kk.[0]]<-(kk.[1],(kk.[2],kk.[3]))::paths.[kk.[0]]
 paths.[kk.[1]]<-(kk.[0],(kk.[2],kk.[3]))::paths.[kk.[1]]
let k_=input()
     //searchList: list of: (island_to_search,(time_of_route_so_far,damage_to_hull_so_far))
let searchList,dest,(visited:(int*int)[])=[(k_.[0],(0,0))],ref k_.[1],Array.init (kk.[1]+1) (fun e-> (-1,0))
let (otherVisited:(int*int)list[])=Array.init (kk.[1]+1) (fun e->[])
//let secondBest=Array.init (kk.[1]+1) (fun e-> (-1,-1))
//let mutable check=false
let rec search (ll:(int*(int*int)) list)=
 let Nlist=ref []
 List.iter (fun (ee:(int*(int*int)))->
  List.iter (fun e->
   let newPath=(fst e,((e|>snd|>fst)+(ee|>snd|>fst),(e|>snd|>snd)+(ee|>snd|>snd)))
   if (newPath|>snd|>snd)<totalHull && (fst visited.[fst newPath]= -1 || (newPath|>snd|>fst)<fst visited.[fst newPath]) then
    visited.[fst newPath]<-newPath|>snd
    Nlist:=newPath:: !Nlist
   elif (newPath|>snd|>snd)<totalHull && (snd visited.[fst newPath]>(newPath|>snd|>snd)) && not(List.exists (fun e->(e|>fst)<=(newPath|>snd|>fst)&&(e|>snd<=(newPath|>snd|>snd))) otherVisited.[fst newPath]) then
    otherVisited.[fst newPath]<-(snd newPath)::otherVisited.[fst newPath]
    Nlist:=newPath:: !Nlist
  ) paths.[fst ee]
 ) ll
 if (!Nlist).Length>0 then search !Nlist// else()
search searchList
System.Console.Out.WriteLine(fst visited.[!dest])


System.Console.ReadLine()