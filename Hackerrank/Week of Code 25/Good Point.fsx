open System
[<Literal>]
let PRECISION = 0.00001
let dist (x1,y1) (x2,y2) = Math.Sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2))
type Space =
  |Line of slope:float*intercept:float*space:bool
  |VerticalLine of xintercept:float*leftspace:bool
  |Ellipse of f1:(float*float)*f2:(float*float)*perim:float
let make_line (x1,y1) (x2,y2) =
  match () with
  |_ when x1 = x2 -> VerticalLine(float x1, y1<y2)
  |_ ->
    let m = float(y2-y1)/float(x2-x1)
    Line(m, float y1-m*float x1, x1 < x2)
let rec intersectLineEllipse_x (Ellipse(p1,p2,R) as e) y (x1,x2) =
  let getR x = dist (x,y) p1 + dist (x,y) p2
  if x2-x1 < PRECISION then getR x1 - PRECISION < R
  else
    let half = (x2+x1)/2.
    if getR (half+PRECISION/2.) < getR half
     then intersectLineEllipse_x e y (half,x2)
     else intersectLineEllipse_x e y (x1,half)
let rec intersectLineEllipse_y (Ellipse(p1,p2,R) as e) x (y1,y2) =
  let getR y = dist (x,y) p1 + dist (x,y) p2
  if y2-y1 < PRECISION then getR y1 - PRECISION < R
  else
    let half = (y2+y1)/2.
    if getR (half+PRECISION/2.) < getR half
     then intersectLineEllipse_y e x (half,y2)
     else intersectLineEllipse_y e x (y1,half)
let intersectPoint (x,y) = function
  |Line(m, b, true) -> y >= m*x+b
  |Line(m, b, false) -> y <= m*x+b
  |Ellipse(p1, p2, R) -> dist p1 (x,y) + dist p2 (x,y) <= R
let intersect (x1,y1) (x2,y2) = function
  |VerticalLine(xi, ls) ->
    (x1 <= xi && xi <= x2) || (xi <= x1 && not ls) || (x2 <= xi && ls)
  |Line(_, _, _) as l ->
    intersectPoint (x1,y1) l || intersectPoint(x1,y2) l
     || intersectPoint (x2,y1) l || intersectPoint (x2,y2) l
  |Ellipse(p1, p2, _) as l ->
    let contained (x,y) =
      (x1 <= x && x <= x2) && (y1 <= y && y <= y2)
    intersectPoint (x1,y1) l || intersectPoint(x1,y2) l
     || intersectPoint (x2,y1) l || intersectPoint (x2,y2) l
     || contained p1 || contained p2
     || intersectLineEllipse_x l y1 (x1,x2) || intersectLineEllipse_x l y2 (x1,x2)
     || intersectLineEllipse_y l x1 (y1,y2) || intersectLineEllipse_y l x2 (y1,y2)

let i = stdin.ReadLine >> int
let ii() = stdin.ReadLine().Split ' ' |> Array.map int
let n = i()
let readPolygon() =
  let v = i()
  let vertices =
    Array.init v (fun _ -> ii())
     |> Array.map (function [|a; b|] -> (a,b))
  List.init v (fun e -> make_line vertices.[e] vertices.[(e+1)%v])
let lines = List.init n (fun _ -> readPolygon()) |> List.concat
let m = i()
let readEllipse() =
  let [|x1; y1; x2; y2; a|] = Array.map float (ii())
  Ellipse((x1,y1), (x2,y2), 2.*a)
let ellipses = List.init m (fun _ -> readEllipse())
let spaces = lines @ ellipses
//printfn "%A" spaces
let gen = System.Random()
let rec src (x1,y1) (x2,y2) =
  if dist (x1,y1) (x2,y2) < PRECISION then Some(x1,y1)
  else
    let x'() = gen.NextDouble()*(x2-x1)+x1
    let y'() = gen.NextDouble()*(y2-y1)+y1
    let xx,yy = (x'()+x'()+x'())/3., (y'()+y'()+y'())/3.
    //let xx,yy = (x1+x2)/2.,(y1+y2)/2.
    //printfn "%A %A %A" (x1,y1) (xx,yy) (x2,y2)
    [(x1,y1),(xx,yy); (xx,y1),(x2,yy); (x1,yy),(xx,y2); (xx,yy),(x2,y2)]
     |> List.fold (fun acc (p1,p2) ->
          match acc with
          |None ->
            if List.forall (intersect p1 p2) spaces then
              src p1 p2
            else None
          |_ -> acc
         ) None
match src (-10000.,-10000.) (10000.,10000.) with
  |Some(a,b) -> printfn "%A\n%A" a b