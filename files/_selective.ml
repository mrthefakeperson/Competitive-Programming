class node v pres=object
 val storedValue:int=v    (*for comparison: the index position in the original input*)
 val mutable sum:int=pres     (*sum of the trunk height of this node and all nodes underneath*)
 val mutable left:node option=None
 val mutable right:node option=None
 method vv=storedValue
 method weight=sum
 method insert n=
  (*n#print();*)
  if n<storedValue
   then match left with
    |Some(e)->e#insert n
	|None->left<-Some(new node n 0)
   else match right with
    |Some(e)->e#insert n
	|None->right<-Some(new node n 0)
 method push n w=
  sum<-sum+w;
  if n<>storedValue then(
   if n<storedValue
    then match left with
     |Some(e)->e#push n w
     |None->()
    else match right with
     |Some(e)->e#push n w
	 |None->()
	)
 method getPrefix n=
  match () with
  |() when n=storedValue->(match left with |Some(e)->e#print();e#weight |None->0)
  |() when n<storedValue->(*left doesn't work*)
   (match left with |Some(e)->e#getPrefix n |None->0)
  |()->(*right*)
   pres+(match left with |Some(e)->e#print();e#weight |None->0)+(match right with |Some(e)->e#getPrefix n |None->0)
 method print()=
  Printf.printf "node value:%i;; (%i underneath)" storedValue sum;
  Printf.printf "\n\tconnected to:%i,%i\n" (match left with |Some(e)->e#vv |None-> -1) (match right with |Some(e)->e#vv |None-> -1);
  (match left with |Some(e)->e#print() |None->());
  (match right with |Some(e)->e#print() |None->())
end;;
let rec readInput n=
 if n=1
  then [(1,(Scanf.scanf "%i" (fun e->e)))]
  else (n,(Scanf.scanf " %i" (fun e->e)))::(readInput (n-1))
let qqq=read_int()
let allHeights=(List.sort (fun a b->
 match () with
 |() when snd a<snd b->1
 |() when snd a=snd b->0
 |()-> -1
) (readInput (qqq)))
let thing=Array.make 100001 false
let tree=new node 50000 0
let rec br place jump=
 if place>=0 && place<=100000 && not thing.(place) then(
  tree#insert place;
  thing.(place)<-true;
  if jump<>1 then(br (place+jump) (jump/2);
  br (place-jump) (jump/2))
  );;
  (*		all nodes must be connected so that all non-bottom nodes have two branches underneath
      something is wrong with sample test case
br 50000 25000;;
	*)
for e=1000 downto 1 do if not thing.(e) then tree#insert e done;;
(*tree#print()*)
let q_=Scanf.scanf "\n%i\n" (fun e->e)
let answers=Array.make q_ 0
let rec readQueries n=
 if n=0
  then []
  else (Scanf.scanf "%i %i %i\n" (fun a b c->((a,b,n),c)))::(readQueries (n-1))
let allQueries=List.sort (fun a b->
 match () with
 |() when snd a<snd b->1
 |() when snd a=snd b->0
 |()-> -1
) (readQueries q_)
let rec sv givenQueries givenData=
 match (givenQueries,givenData) with
 |(thisQuery::queryTl,thisData::dataTl)->
  if snd thisQuery<=snd thisData
   then 
    (
	  tree#push (fst thisData) (snd thisData);
    sv givenQueries dataTl)
   else((
    (match fst thisQuery with
	|(low,high,ansIndex)->
	 answers.(ansIndex-1)<-(tree#getPrefix (high+1))-(tree#getPrefix (low))
	));sv queryTl givenData)
 |(thisQuery::queryTl,[])->(
  (match fst thisQuery with
  |(low,high,ansIndex)->
   answers.(ansIndex-1)<-(tree#getPrefix (high+1))-(tree#getPrefix (low))
  ));sv queryTl []
 |([],_)->();;
(*
List.iter (fun e->match e with |((a,b,n),c)->Printf.printf "query %i: from %i to "
*)
sv allQueries allHeights;;
Array.iter (Printf.printf "%i\n") answers
(*Printf.printf "%i" (tree#getPrefix (read_int()))*)