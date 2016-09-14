public class Uses_Fraction
{
	public static void main(String[] args)
	{
		Fraction hidden = new Fraction(10, 66);
		System.out.println(hidden.getNum() + " / " + hidden.getDen());
		hidden.setNum(5);
		System.out.println(hidden.getNum() + " / " + hidden.getDen());
		hidden.setDen(0);
		System.out.println(hidden.getNum() + " / " + hidden.getDen());
	}//end main
}//end class Uses_Fraction