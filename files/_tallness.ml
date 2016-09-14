let split s on=
	let m=String.index s on in
	(int_of_string(String.sub s 0 (m)),int_of_string(String.sub s (m+1) ((String.length s)-m-1)));;
let getLine ()=
	split (input_line stdin) ' ';;
let __=getLine();;
let allPeople=Array.make (fst __) [];;
for e=1 to (snd __) do
	let _3=getLine() in
	allPeople.((fst _3)-1)<-(snd _3)-1::(allPeople).((fst _3)-1)
done;;
let tall,short=getLine();;
let k=ref false;;
let taller=allPeople.(tall-1);;
let shorter=allPeople.(short-1);;
(*
let rec search thing forWhat=
	let (q:int list ref)=ref [] in
	(*List.iter (fun x->Printf.printf "%i " (x+1)) thing;*)
	(*Printf.printf "for:%i\n" (forWhat+1);*)
	match thing with
	|_ when (List.exists (fun x->x=forWhat) thing)->true
	|_ when (List.length thing)=0->false
	|_->
		for e=0 to (List.length thing)-1 do
			q:=((!q)@(allPeople.(List.nth thing e)))
		done;
		search (!q) forWhat;;
*)
let visited=Array.make (Array.length allPeople) false;;
let rec search thisList forWhat=
	match thisList with
	|[]->false
	|_ when List.exists (fun x->x=forWhat) thisList->true
	|_->
		let kk=ref false in
		for e=0 to (List.length thisList)-1 do
			let tt=List.nth thisList e in
			match 0 with
			|_ when visited.(tt)=true->()
			|_ when search allPeople.(tt) forWhat ->
				kk:=true
			|_->
				visited.(tt)<-true
		done;
		!kk;;
match 1 with
|_ when (search taller (short-1))->
	print_string "yes"
|_->
	for e=0 to (Array.length visited)-1 do visited.(e)<-false done;
	match 2 with
	|_ when (search shorter (tall-1))->
		print_string "no"
	|_->print_string "unknown";;