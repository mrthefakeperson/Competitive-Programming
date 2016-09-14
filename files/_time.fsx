open System.IO
let inp=new StreamReader(System.Console.OpenStandardInput())
let n,t=
 match inp.ReadLine().Split [|' '|] with
 |[|a;b|]->(int a,int b)
let mutable column:int[]=Array.zeroCreate (t+1)
for ee in 1..n do
 match Array.map int (inp.ReadLine().Split [|' '|]) with
 |[|a;b;c;d;e;f|]->
  //Array.iteri (printf "%A:%A   ") column
  column<-
   Array.mapi (fun i e_->
    let mutable maxx=e_
    if i-a>=0 && column.[i-a]+b>maxx then maxx<-column.[i-a]+b
    if i-c>=0 && column.[i-c]+d>maxx then maxx<-column.[i-c]+d
    if i-e>=0 && column.[i-e]+f>maxx then maxx<-column.[i-e]+f
    maxx
   ) column

//Array.iteri (printf "%A:%A   ") column

System.Console.Out.WriteLine(column.[t])



System.Console.ReadLine()