open System
let k=int (Console.ReadLine())
let start=Environment.TickCount
let me=ref [2..k]
let mutable (mine:int list)=[]
//let mutable ind=0
while (!me).Length>0 do
 let kk=(!me).[0]
 me:=List.filter (fun x->x%kk<>0) (!me)
 //printfn "%A" !me
 mine<-kk::mine
printfn "%A" (Environment.TickCount-start)
printfn "%A" mine
Console.ReadLine()