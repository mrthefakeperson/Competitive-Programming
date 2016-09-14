import java.util.Scanner;
public class bessarion
{	public static void main(String args[])
	{	Scanner _=new Scanner(System.in);
		int e=Integer.parseInt(_.nextLine());
		String sta[]=new String[e];
		for(int k=0;k<e;k++)
		{	sta[k]=_.nextLine();
		}
		boolean ans=false;
		System.out.print(e);
		for(int k=0;k<e-2;k++)
		{	System.out.print(sta[k]+sta[k+1]+sta[k+2]);
			if(sta[k+1].Equals(Bessarion) && ((sta[k].Equals("Bayview") && sta[k+2].Equals(Leslie))||(sta[k+2].Equals("Bayview") && sta[k].Equals(Leslie))))
			{	ans=true;System.out.print("d");
			}
		}
		System.out.print((ans)?"Y":"N");
	}
}