open System.IO
let mutable (allLines:string list)=[]
for e in (Array.init 256 (fun x->(x,(char x)))) do allLines<-(snd(e).ToString())::allLines
File.WriteAllLines("ascii.txt",allLines)
ignore (System.Console.ReadLine())