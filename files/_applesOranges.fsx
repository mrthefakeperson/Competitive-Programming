open System.IO
let inp=new StreamReader(System.Console.OpenStandardInput())
let n,m=match inp.ReadLine().Split(' ') with
        |[|a;b|]->(int a,int b)
let lookup=
 Seq.init n (fun e->(inp.ReadLine(),e))|>dict
let exchangeAdj:(int*bigint) list[]=Array.init m (fun e->[])
for e in 1..m do
 match inp.ReadLine().Split(' ') with
 |[|a;b;rate|]->
  exchangeAdj.[lookup.[a]]<-(lookup.[b],bigint((float rate)*1000000000000.))::exchangeAdj.[lookup.[a]]

//printfn "%A" exchangeAdj

let apples=lookup.["APPLES"]
//most which can be obtained so far
let visited=Array.init n (fun _->0I)
visited.[apples]<-1000000000000I
//let searchList=[(apples,1.)]
let rec search=function
|_ when visited.[apples]>1000000000000I(* && (Array.forall (fun e->e>0.) visited)*)->System.Console.Out.WriteLine("YA")
|[]->System.Console.Out.WriteLine("NAW")
|ll->
 //printfn "%A" ll
 search (
  List.collect (fun fruit->
   //let nn=
    List.choose (fun exchange->
     let newItem,newPrice=fst exchange,snd exchange*snd fruit/1000000000000I
     //printfn "%A,%A" newItem newPrice
     if visited.[newItem]<newPrice then
      visited.[newItem]<-newPrice
      Some((newItem,newPrice))
     else
      None
    ) exchangeAdj.[fst fruit]
   //printfn "nn:%A" nn
   //nn
  ) ll
 )
search [(apples,1000000000000I)]
//printfn "%A" visited

System.Console.ReadLine()