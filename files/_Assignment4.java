import java.util.Scanner;
public class Assignment4
{
	public static void main(String[] args)
	{
		Scanner mr_scans=new Scanner(System.in);
		System.out.println("License and registration please. Do you know what speed you were driving at?");
		int spd=mr_scans.nextInt();
		System.out.println("...also, is it your birthday?");
		mr_scans.nextLine();		//nextInt() doesn't scan for the line break
		String yesNo=mr_scans.nextLine();
		if (yesNo.equals("yes")){
			spd-=5;
		}
		System.out.print("Thanks for playing!!! Your prize is... ");
		if (spd<=60){
			System.out.println("Nothing!");
		}
		else if (spd>=81){
			System.out.println("a BIG ticket.");
		}
		else{
			System.out.println("a small ticket.");
		}
	}
}