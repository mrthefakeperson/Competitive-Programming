import java.util.Scanner;
public class EasySort
{
	public static void selectionSort(int[] ll, int places)
	{
		for (int e = ll.length - 1; e > ll.length - 1 - places; e--)
		{
			int accI = e, accM = ll[e];
			for (int ee = 0; ee <= e; ee++)
			{
				if (accM < ll[ee]) 
				{
					accI = ee;
					accM = ll[ee];
				}
			}
			//swap
			int _ = ll[e];
			ll[e] = ll[accI];
			ll[accI] = _;
		}
	}
	public static void main(String[] args)
	{
		int[] ll = {3,2,1,5,4, 9, 10, 0,3,4,5,1};
		selectionSort(ll, 3);
		for (int e : ll) System.out.println(e);
	}
}//end class EasySort