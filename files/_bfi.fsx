open System.IO
[<EntryPoint>]
let main (argv:string[])=
 let mutable path=""
 if argv.Length=0 then 
  path<-System.Console.ReadLine()
 else
  path<-argv.[0]
 let k=File.ReadAllText(path)
 let mutable (data:byte[]),point=Array.zeroCreate 30000,0
 let mutable e,brackets=0,0
 while e<k.Length do
  match k.[e] with
  |'+'->data.[point]<-data.[point]+1uy
  |'-'->data.[point]<-data.[point]-1uy
  |'>'->point<-point-1
  |'<'->point<-point+1
  |','->data.[point]<-System.Console.Read()|>byte
  |'.'->printf"%O" (char data.[point])
  |'['->
   brackets<-1
   if data.[point]=0uy then
    while brackets<>0 do
     e<-e+1
     if k.[e]='[' then brackets<-brackets+1
     elif k.[e]=']' then brackets<-brackets-1
  |']'->
   brackets<-1
   if data.[point]<>0uy then
    while brackets<>0 do
     e<-e-1
     if k.[e]=']' then brackets<-brackets+1
     elif k.[e]='[' then brackets<-brackets-1
  |_->()
  //printfn"this instruction:%O\nthis instruction Point:%A\nvalue:%A\nposition:%A" k.[e] e !data.[point] point
  //System.Console.ReadLine()|>ignore
  e<-e+1
  if point=30000 then point<-0
  elif point= -1 then point<-29999
 //System.Console.ReadLine()|>ignore
 0
//main [||]