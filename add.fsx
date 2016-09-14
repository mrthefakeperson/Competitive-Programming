(*
    script for adding new files to the files\ directory
    currently supports:
      - addition of all files under a directory
      - renaming files based on their position in a given directory
      - renaming files which already exist in the files\ directory
      - filtering so that only files with supported extensions are added
    in the future, it may support:
      - database-like querying of specific files (based on names and dates modified)
      - a virtual file system, where files can be arbitrarily sorted and organized into a directory structure
*)

open System.IO
open System.Text.RegularExpressions
open System

let recognized_extensions = File.ReadAllLines "file extensions.txt"
match Environment.GetCommandLineArgs() with
  [|"fsi"; "add.fsx"; directory_name|] ->
    let rec flattenFiles dir =
      Array.append
       (Directory.GetFiles dir)
       (Array.collect flattenFiles (Directory.GetDirectories dir))
    let ext (file:string) sep =
      let a = file.Split [|sep|]
      a.[a.Length-1]
    flattenFiles directory_name
     |> Array.filter (fun e -> Array.exists ((=) (ext e '.')) recognized_extensions)
     |> Array.iter (fun e ->
          let fileName' = e.Replace(directory_name,"").Replace('\\','_')
          printfn "%A" fileName'
          if File.Exists(@"files\"+fileName')
           then File.Copy(e,@"files\"+string Environment.TickCount+" "+fileName')
           else File.Copy(e,@"files\"+fileName')
         )
  |_ -> ()