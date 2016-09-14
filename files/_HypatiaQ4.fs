let gcd n1 n2=
 let factor n=
  [for e in 1..n do
    if n%e=0 then yield n/e]
 let l1=factor n1
 let l2=factor n2
 //let intersct=List.filter (fun e1->List.exists ((=)e1) l2) l1
 //intersct.[0]
 let ret=List.find (fun e1->List.exists ((=)e1) l2) l1
 ret

[<EntryPoint>]
let main argv=
 let q1=int (System.Console.ReadLine())
 let k=ref 1
 let me=ref 0
 while !k<q1 do
  me:=0
  for e in 1..!k do
   me:=(gcd !k e)+ !me
   //printfn "gcd(%A,%A)=%A:::total:%A" !k e (gcd !k e) !me
  //printfn "k: %A me: %A" !k !me
  if !me=q1 then printfn "%A" !k
  k:=!k+1
 printfn "done!"
 ignore (System.Console.ReadLine())
 0
