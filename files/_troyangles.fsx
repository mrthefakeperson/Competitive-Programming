let w,total=System.Console.In.ReadLine()|>int,ref 0L
let data=Array.init w (fun e->System.Console.In.ReadLine())
let itemsAtPeak=Array2D.init w w (fun x y->
 match data.[x].[y] with
 |'.'->0L
 |_-> -1L
 )
for x in 0..w-1 do
 match itemsAtPeak.[w-1,x] with
 | -1L->
  itemsAtPeak.[w-1,x]<-1L
  total:= !total+1L
 |_->()
//printfn "%A" itemsAtPeak
for y in w-2..-1..0 do
 for x in 0..w-1 do
  if itemsAtPeak.[y,x]<>0L then
   let minFrom=Array.init 3 (fun e->
    match x-e+1 with
    | -1->0L
    |q when q=w->0L
    |q->itemsAtPeak.[y+1,q]
   )
   //let minFrom=[|for ee in (max (x-1) 0)..(min (x+1) (w-1)) do yield itemsAtPeak.[y+1,ee]|]
   let inc=((Array.min minFrom)|>int64)+1L
   itemsAtPeak.[y,x]<-inc
   total:= !total+inc
//printfn "%A" itemsAtPeak
System.Console.Out.WriteLine(!total)


System.Console.ReadLine()