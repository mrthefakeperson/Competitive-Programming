import java.util.Scanner;
public class Assignment2
{
	public static void main(String[] args)
	{
		Scanner mr_scans=new Scanner(System.in);
		System.out.println("Enter your day-number:");
		boolean[] weekdays={false,true,true,true,true,true,false};
		
		boolean isWeekDay=weekdays[mr_scans.nextInt()];
		System.out.println("true or false: are you on vacation?");
		boolean isVacationTime=mr_scans.nextBoolean();

		System.out.print("The alarm is set to ");
		if (isWeekDay){
			if (isVacationTime){
				System.out.println("10:00.");
			}
			else{
				System.out.println("7:00.");
			}
		}
		else{
			if (isVacationTime){
				System.out.println("off.");
			}
			else{
				System.out.println("10:00.");
			}
		}
	}
}