open System
open System.IO

let updateWord (chosen:string) (guess:string) (word:string[] ref)=
 let (k:int)=chosen.IndexOf(guess)
 let Nchosen=chosen.Remove(k,1).Insert(k,"&")
 let Nword=
  [|for e in 0..(!word).Length-1 do
     if e=k then
      yield guess
     else
      yield (!word).[e]|]
 (Nchosen,Nword)
let matchWithWord (x:string) (word:string[])=
 let mutable k=true
 for e in 0..x.Length-1 do
  if word.[e]<>"_" && word.[e]<>x.Substring(e,1) then
   k<-false
 k

[<EntryPoint>]
let main argv=
 System.Console.Title<-"Evil Hangman"
 let dict=ref (File.ReadAllLines("dict.txt"))
 //printfn "%A" dict
 let rnd=new System.Random()
 let rand()=(rnd).Next(dict.Value.Length)
 let r=rand()
 let word=ref (Array.init (!dict).[r].Length (fun x->"_"))
 dict:=Array.filter (fun x->x.Length=(!word).Length) !dict
 //printfn "%A\n%A" word !dict
 let mutable chosen=""
 let guesses=ref []
 let pr()=
  printfn "\n\n  "
  for e in !word do printf "%s  " e
  printfn "\n\nguesses:"
  for e in !guesses do printf "\t%s" e
  printfn ""
 while (Array.exists ((=) "_") (!word)) do
  pr()
  printfn "guess:"
  let guess=ref (System.Console.ReadLine())
  while List.exists ((=) !guess) !guesses do
   System.Console.Beep()
   printfn "guess again:"
   guess:=System.Console.ReadLine()
  if (Array.exists (fun (x:string)->not (x.Contains(!guess))) !dict) then
   dict:=Array.filter (fun (x:string)->not (x.Contains(!guess))) !dict
   if (not (Array.exists ((=) chosen) !dict)) then
    chosen<-dict.Value.[(rand())]
  else
   dict:=Array.filter (fun (x:string)->x.Contains(!guess)) !dict
   if chosen="" then
    chosen<-dict.Value.[(rand())]
   while chosen.Contains(!guess) do
    let L=(updateWord chosen !guess word)
    chosen<-fst(L)
    word:=snd(L)
   chosen<-chosen.Replace("&",!guess)
  dict:=Array.filter (fun x->matchWithWord x !word) !dict
  guesses:=(!guess)::(!guesses)
  System.Console.Clear()
  //printfn "%A\nguesses: %A\n\nchosen: %A\n\t%A" !word guesses chosen !dict
 pr()
 ignore (System.Console.ReadLine())
 0