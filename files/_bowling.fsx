let t=System.Console.In.ReadLine()|>int

let oneCase()=
 let ii=System.Console.In.ReadLine().Split [|' '|]
        //w might be even
 let numBalls,w,pins=ii.[1]|>int,ii.[2]|>int,ref (Array.init (ii.[0]|>int) (fun e->System.Console.In.ReadLine()|>int))
 let pinOptimize=ref (Array.mapi (fun i e->List.init w (fun n->
                                                                let kk=i+n
                                                                if kk<(!pins).Length then (!pins).[kk] else 0
                                                             )|>List.sum
                                 ) !pins)
 let pinBeginning= !pinOptimize
                                 (*
 let knockOver=Array2D.init (!pins).Length (w+3) (fun x y->
                                                   List.init (2*w+1-y) (fun n->
                                                                        let kk=x-w+n
                                                                        if kk>=0 && kk<(!pins).Length then (!pins).[kk] else 0
                                                                       )|>List.sum|>((-) (!pinOptimize).[x])
                                                 )
*)
 //printfn "%A -knockedOver\n%A" knockOver !pinOptimize
 for e in 2..numBalls do
  let temp=ref 0
  let biggestValLeft=
   let tt=
    Array.map (fun e->if e> !temp then temp:=e
                      !temp
              ) !pinOptimize
   tt|>(Array.mapi (fun i e->
                      if i-w<0 then 0 else tt.[i-w]
                   ))
  pinOptimize:=Array.mapi2 (fun i e1 e2->
                             e1+e2
                           ) pinBeginning biggestValLeft//.[0..(!pinOptimize).Length-1]
  //printfn "%A" !pinOptimize
 if (numBalls*w>= (!pins).Length) then System.Console.WriteLine(Array.sum !pins)
 else System.Console.Out.WriteLine(Array.max !pinOptimize)

for e in 1..t do oneCase()



System.Console.ReadLine()