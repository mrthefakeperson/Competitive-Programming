public class Fraction
{
	private int num;
	private int den;
	public Fraction ()
	{
		this(0, 1);
	}//end constructor Fraction()
	public Fraction (int num, int den)
	{
		this.num = num;
		this.den = den;
	}//end constructor Fraction(int, int)
	public Fraction (Fraction copy)
	{
		this(copy.num, copy.den);
	}//end constructor Fraction(Fraction)
	public void setNum (int to)
	{
		this.num = to;
	}//end member setNum
	public int getNum ()
	{
		return this.num;
	}//end member getNum
	public void setDen (int to)
	{
		if (to == 0)
			this.den = 1;
		else
			this.den = to;
	}//end member setDen
	public int getDen ()
	{
		return this.den;
	}//end member getDen
	public double size ()
	{
		return Math.abs((double) this.num / this.den);
	}//end member size
	public Fraction larger (Fraction other)
	{
		if (this.size() >= other.size())
			return this;
		else
			return other;
	}//end member larger
	public void plusEquals (Fraction other)
	{
		this.num = this.num * other.den;
		this.num += other.num * this.den;
		this.den = this.den * other.den;
	}//end member plusEquals
	public Fraction plus (Fraction f)
	{
		Fraction next = new Fraction();
		next.den = this.den * f.den;
		next.num = this.num * f.den + f.num * this.den;
		return next;
	}//end member plus
	public Fraction times (Fraction f)
	{
		Fraction next = new Fraction();
		next.num = this.num * f.num;
		next.den = this.den * f.den;
		next.reduce();
		return next;
	}//end member times
	private static int HELP (int low, int high)
	{
		if (low > high)
			return HELP(high, low);
		else if (low == 0)
			return high;
		else
			return HELP(low, high % low);
	}//end member HELP
	public void reduce ()
	{
		int gcd = HELP(this.num, this.den);
		this.num /= gcd;
		this.den /= gcd;
	}//end member reduce
}//end class Fraction