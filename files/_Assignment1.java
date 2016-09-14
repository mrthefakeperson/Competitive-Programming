import java.util.Scanner;
public class Assignment1
{
	public static void main(String[] args)
	{
		Scanner mr_scans=new Scanner(System.in);
		System.out.println("Enter your numbers, seperated by a line or a space:");
		int _a=mr_scans.nextInt(),_b=mr_scans.nextInt();
		int _sum=_a+_b;
		if (_sum>=10 && _sum<=17){
			System.out.println("no sum");
		}
		else{
			System.out.println(_sum);
		}
	}
}