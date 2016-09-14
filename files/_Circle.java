public class Circle
{
	private double x;
	private double y;
	private double r;
	public void setX (double to)
	{
		this.x = to;
	}//end member setX
	public double getX ()
	{
		return this.x;
	}//end member getX
	public void setY (double to)
	{
		this.y = to;
	}//end member setY
	public double getY ()
	{
		return this.y;
	}//end member getY
	public void setR (double to)
	{
		if (this.r < 0)
			r = 0;
		else
			r = to;
	}//end member setR
	public double getR ()
	{
		return this.r;
	}//end member getR
	public double area()
	{
		return Math.PI * this.r * this.r;
	}//end member area
	public Circle smaller(Circle compare)
	{
	if (this.r <= compare.r)
		return this;
	else
		return compare;
	}//end member smaller
	//returns whether one circle eclipses another or not
	//if the absolute value distance between centres added to 
	//the radius of the comparing circle is smaller than
	//the radius of the object circle, then true
	public boolean isInside(Circle compare)
	{
		double distance = Math.sqrt(
					Math.pow(this.x - compare.x, 2) + 
					Math.pow(this.y - compare.y, 2) );
		//if the circles touch at a single point, then it is still eclipsed
		return (distance + this.r <= compare.r);
	}//end member isInside
}//end class Circle