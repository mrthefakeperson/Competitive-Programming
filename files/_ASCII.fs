for e in (Array.init 256 (fun x->(x,(char x)))) do printf "%5s: %O" (fst(e).ToString()) (snd(e))
ignore (System.Console.ReadLine())