let rand=new System.Random()
let makeList()=
 let k()=rand.Next(4)
 let mutable r=[]
 let ll=ref (k())
 r<- !ll::r
 while r.Length<>4 do
  if not (List.exists ((=) !ll) r) then
   r<- !ll::r
  ll:=k()
 r
let printMe (me:int[,]) inpX inpY=
 let mutable pr=""
 for yy in 0..inpY-1 do
  for xx in 0..inpX-1 do
   match me.[xx,yy] with
   |0->pr<-pr+" "
   |_->pr<-pr+(char 198).ToString()
  pr<-pr+"\n"
 printf "%O" pr
let rec adv x y X Y (maze:int[,]) (thing:float)=
 maze.[x,y]<-1
 let lst=makeList()
 for e in lst do
  System.Console.Clear()
  printMe maze X Y
  let kk=System.Environment.TickCount
  while System.Environment.TickCount-kk<40-(int thing) do
   ignore 0
  match e with
  |0 when (y+2>0 && y+2<Y && maze.[x,y+2]<>1)->
   maze.[x,y+1]<-1
   adv x (y+2) X Y maze thing
  |1 when (x-2>0 && x-2<X && maze.[x-2,y]<>1)->
   maze.[x-1,y]<-1
   adv (x-2) y X Y maze thing
  |2 when (y-2>0 && y-2<Y && maze.[x,y-2]<>1)->
   maze.[x,y-1]<-1
   adv x (y-2) X Y maze thing
  |3 when (x+2>0 && x+2<X && maze.[x+2,y]<>1)->
   maze.[x+1,y]<-1
   adv (x+2) y X Y maze thing
  |_->ignore 0

[<EntryPoint>]
let main argv=
 let inpX,inpY=int (System.Console.ReadLine()),int (System.Console.ReadLine())
 System.Console.SetWindowSize(inpX+5,inpY+5)
 let me=(Array2D.zeroCreate inpX inpY)
 adv 0 0 inpX inpY me ((float (inpX+inpY))/2.0)
 System.Console.Clear()
 printMe me inpX inpY
 printfn "done"
 ignore (System.Console.ReadLine())
 0