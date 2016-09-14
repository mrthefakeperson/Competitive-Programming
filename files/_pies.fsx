open System.IO
open System
let inp=StreamReader(Console.OpenStandardInput())
let n=inp.ReadLine()|>int
let pies=Array.init n (fun _->inp.ReadLine()|>int)
let m=inp.ReadLine()|>int
let otherPies=Array.init m (fun _->inp.ReadLine()|>int)|>Array.sort
let visited= //Array3D.create (n+1) (m+1) (m+1) 0
 Array.init (n+1) (fun e->
  Array.init (m+1) (fun e->
   Array.create (m-e+1) 0
  )
 )

let rec getSugar place low high=
 //printfn "%A/%A/%A" place low high
 match (place,high) with
 |(0,0)->0
 |(0,1)->otherPies.[m-1]
 |(1,0)->pies.[0]
 |_->
   if visited.[place].[low].[high]=0 then
    visited.[place].[low].[high]<-
     let mutable mxx=0
     if place>0 then mxx<-Math.Max(mxx,getSugar (place-1) low high)
     if low>0 then mxx<-Math.Max(mxx,getSugar place (low-1) high)
     
     if place>=2 then mxx<-Math.Max(getSugar (place-2) low high+pies.[place-1],mxx)
     if place>=1 && low>=1 then mxx<-Math.Max(getSugar (place-1) (low-1) high+pies.[place-1],mxx)
     if low>=1 && high>=1 then mxx<-Math.Max(getSugar place (low-1) (high-1)+otherPies.[m-high],mxx)
     if place>=1 && high>=1 then mxx<-Math.Max(getSugar (place-1) low (high-1)+otherPies.[m-high],mxx)
     mxx
   visited.[place].[low].[high]
   
let mutable mm=0
for e in 0..m do
 mm<-Math.Max(mm,getSugar n e (m-e))
//Console.Out.Write mm
let a=StreamWriter(Console.OpenStandardOutput())
a.Write mm
a.Flush()

Console.ReadLine()