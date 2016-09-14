let factorLowest n=
 let mutable k_=2
 while n%k_<>0 do k_<-k_+1
 k_
let mutable nn,points=System.Console.ReadLine()|>int,0
while nn<>1 do
 let lowest=factorLowest nn
 points<-points+lowest-1
 nn<-nn/lowest*(lowest-1)
System.Console.WriteLine(points)



System.Console.ReadLine()