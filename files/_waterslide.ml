let split s on=
	let m=String.index s on in
	(int_of_string(String.sub s 0 (m)),int_of_string(String.sub s (m+1) ((String.length s)-m-1)));;
let k=int_of_string(input_line stdin);;
let slides=Array.make (k+1) 0;;
slides.(k)<-1;;
let paths=ref [];;
let __=ref (split (input_line stdin) ' ');;
while fst !__<>0 do
	paths:=(snd !__,fst !__)::!paths;
	__:=split (input_line stdin) ' '
done;;
let tt a b=
	compare (fst a) (fst b);;
let vecs=List.rev (List.stable_sort tt !paths);;
(*
for ind=0 to (List.length vecs)-1 do
	let e=List.nth vecs ind in
	slides.(snd e)<-slides.(snd e)+slides.(fst e)
done;;*)
List.iter (fun e->slides.(snd e)<-slides.(snd e)+slides.(fst e)) vecs;;
print_int slides.(1);;