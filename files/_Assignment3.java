import java.util.Scanner;
public class Assignment3
{
	public static void main(String[] args)
	{
		Scanner mr_scans=new Scanner(System.in);
		System.out.println("Enter the number of words.");
		int words=mr_scans.nextInt();
		double cost=8.5;
		if (words>15){
			cost+=(words-15)*0.25;
		}
		System.out.format("Your telegram costs $%.2f.",cost);
	}
}