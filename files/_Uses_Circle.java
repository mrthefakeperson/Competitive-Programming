public class Uses_Circle
{
	public static void main(String[] args)
	{
		//assign and initialize
		Circle c1 = new Circle(), c2 = new Circle();
		c1.x = 4;
		c1.y = -1;
		c1.r = 3;
		c2.x = 3;
		c2.y = -2;
		c2.r = 5;
		
		System.out.println(c1.area());
		Circle HELP = c1.smaller(c2);
		System.out.println(HELP.x + "," + HELP.y + "\n" + HELP.r);
		if (c2.isInside(c1))
			System.out.println("an appropriate statement");
	}
}