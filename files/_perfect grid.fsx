module pGrid=
 open System
 open System.IO
 let pGrid()=

  let stdin=new StreamReader @"C:\Users\Thefak\Desktop\programming\F#\input.txt"
  let stdout=new StreamWriter @"C:\Users\Thefak\Desktop\programming\F#\output.txt"

  let n=stdin.ReadLine() |> int
  let a,b,c,d,e=
   let gen key=List.filter (((&&&) key) >> ((<>) 0)) [0..31]
   gen 0b10000,gen 0b01000,gen 0b00100,gen 0b00010,gen 0b00001
  let vertical_lines=Array.init 32 (fun _->Array.create n 0L)
  let rectangulation rowNumber lines=
   let hull,acc=ref [(-1L,int64 rowNumber)],ref 0L
   Array.iteri (fun i e->
    while snd (!hull).Head<e do
      let left,right,centre=fst (!hull).Tail.Head,int64 i,fst (!hull).Head
      let wl,wr=centre-left,right-centre
      let h=rowNumber-snd (!hull).Head
      acc:= !acc+wl*wr*h
      hull:=(!hull).Tail
    hull:=(int64 i,e):: !hull
   ) (Array.append lines [|rowNumber|])
   //printfn "rectangulated %A, row %A; found %A unique subgrids" lines rowNumber !acc
   !acc
  let subsetErrands rowNumber=
  //let a=ref []
   Seq.init 32 (fun e->
    let setBits=
      seq {yield 0b10000; yield 0b01000; yield 0b00100; yield 0b00010; yield 0b00001}
       |> Seq.sumBy (fun ee->if ee &&& e <> 0 then 1 else 0)
       (*
    seq {yield ("A",0b10000); yield ("B",0b01000); yield ("C",0b00100); yield ("D",0b00010); yield ("E",0b00001)}
     |> Seq.map (fun (a,ee)->if ee &&& e <> 0 then a else "")
     |> Seq.reduce (+)
     |> fun e'->printfn "%A from %A; %A" (rectangulation rowNumber vertical_lines.[e]) vertical_lines.[e] e';e'
     |> fun e'->a:=(e',rectangulation rowNumber vertical_lines.[e]):: !a
     *)
    if setBits % 2 = 0
     then rectangulation rowNumber vertical_lines.[e]
     else -(rectangulation rowNumber vertical_lines.[e])
   )
   |> Seq.sum
   (*
   |> fun e->
        printfn "%A" (List.sortBy (fst >> String.length) !a)
        e
        *)
  {1..n}
  |> Seq.sumBy (fun rowNumber->
      stdin.ReadLine().ToCharArray()
       |> Array.iteri (fun i e'->
            let thing=
              match e' with
              |'A'->a |'B'->b |'C'->c |'D'->d |'E'->e |_->[]
            List.iter (fun e->
              vertical_lines.[e].[i]<-int64 rowNumber
             ) thing
           )
      let a=subsetErrands (int64 rowNumber)
      //printfn "%A: %A subgrids contain all letters" rowNumber a
      a
     )    //overflow problems
  |> stdout.WriteLine

  stdin.Close()
  stdout.Flush()
  stdout.Close()

pGrid.pGrid()