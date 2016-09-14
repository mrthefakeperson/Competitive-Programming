let findWord word L=
 List.exists ((=) word) L
let tryStop (word:string) L=
 List.exists (fun (x:string)->x.Length<word.Length) L
[<EntryPoint>]
let main argv=
 let word=(System.Console.ReadLine())
 let mutable L=["a"]
 let mutable nextEs=["a"]
 let count=ref 1
 let mutable current=""
 while not(findWord word L) && (tryStop word nextEs) do
  count:=!count+1
  nextEs<-[]
  for e in L do
   current<-"b"+e+"s"
   if word.Contains(current) && not (findWord current L) && not (findWord current nextEs) then
    nextEs<-current::nextEs
   for e2 in L do
    current<-e+"n"+e2
    if word.Contains(current) && not (findWord current L) && not (findWord current nextEs) then
     nextEs<-current::nextEs
  L<-L@nextEs
  printfn "%A %A" L !count
 if not (findWord word L) then
  printf "could not find"
 ignore (System.Console.ReadLine())
 0