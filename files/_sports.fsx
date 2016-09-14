let t=System.Console.In.ReadLine()|>int
for e in 1..t do
 let ll=System.Console.In.ReadLine().Split [|'-'|]
 let win,loss=int ll.[0]+1,int ll.[1]+1
 //right:point for you; down:point for other team
 let mutable startStressfree,startStressful=[(1,0)],[(0,0)]
 let stressfree,stressful=Array2D.init win loss (fun x y->if x>y then 0 else -1),Array2D.init win loss (fun x y->if x<=y || y=loss-1 then 0 else -1)
 stressfree.[1,0]<-1
 stressful.[0,0]<-1
 //stressful.[win-1,loss-1]<-0
 while startStressfree.Length>0 do
  let mutable Nlist=[]
  for e in startStressfree do
   if fst e+1<win then
    if stressfree.[fst e+1,snd e]=0 then Nlist<-(fst e+1,snd e)::Nlist
    stressfree.[fst e+1,snd e]<-(stressfree.[fst e+1,snd e]+stressfree.[fst e,snd e])%1000000007
   if snd e+1<loss then
    if stressfree.[fst e,snd e+1]<> -1 then
     if stressfree.[fst e,snd e+1]=0 then Nlist<-(fst e,snd e+1)::Nlist
     stressfree.[fst e,snd e+1]<-(stressfree.[fst e,snd e+1]+stressfree.[fst e,snd e])%1000000007
  startStressfree<-Nlist
 System.Console.Out.Write(stressfree.[win-1,loss-1])
 while startStressful.Length>0 do
  let mutable Nlist=[]
  for e in startStressful do
   if fst e+1<win then
    if stressful.[fst e+1,snd e]<> -1 then
     if stressful.[fst e+1,snd e]=0 then Nlist<-(fst e+1,snd e)::Nlist
     stressful.[fst e+1,snd e]<-(stressful.[fst e+1,snd e]+stressful.[fst e,snd e])%1000000007
   if snd e+1<loss then
    if stressful.[fst e,snd e+1]=0 then Nlist<-(fst e,snd e+1)::Nlist
    stressful.[fst e,snd e+1]<-(stressful.[fst e,snd e+1]+stressful.[fst e,snd e])%1000000007
  startStressful<-Nlist
 System.Console.Out.WriteLine(" "+string stressful.[win-1,loss-1])
 //printfn "%A \n%A" stressfree stressful