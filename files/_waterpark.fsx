let (points:int list[])=Array.init ((System.Console.ReadLine()|>int)+1) (fun _->[])
let mutable mm=(1,1)
while mm<>(0,0) do
 let inn=System.Console.ReadLine().Split [|' '|]
 mm<-(inn.[0]|>int,inn.[1]|>int)
 points.[snd mm]<-fst mm::points.[snd mm]
let ways:int[]=Array.zeroCreate (points.Length)
ways.[ways.Length-1]<-1
for e in points.Length-1..-1..1 do
 for ee in points.[e] do
  ways.[ee]<-ways.[ee]+ways.[e]
System.Console.WriteLine(ways.[1])