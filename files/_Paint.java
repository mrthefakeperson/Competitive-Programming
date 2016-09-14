/**
 * created 09/10/2015, for ICS4U1
 * 
 * creates paint management objects which retain information about colours,
 * represents amount of red, green, and blue colours as doubles for amounts of different paints in litres
 * and manages cost given a set price model (for red, green, and blue paint)
 *
 * @author Charles Lei
 */

import java.util.Scanner;

public class Paint
{
	
	/**********		*
	 * Constants
	 **********		*/
	
	//designated price per litre for red paint
	public static final double RED_PRICE = 2.00;

	//designated price per litre for green paint
	public static final double GREEN_PRICE = 3.50;

	//designated price per litre for blue paint
	public static final double BLUE_PRICE = 4.25;
	
	/**********		*
	 * Instance variables
	 **********		*/

	//holds the quantity of red paint (litres), it must always be at least 0
	private double qRed;

	//holds the quantity of green paint (litres), it must always be at least 0
	private double qGreen;
	
	//holds the quantity of blue paint (litres), it must always be at least 0
	private double qBlue;
	
	/**********		*
	 * Constructors
	 **********		*/

	/**
	 * default constructor.
	 * constructs a Paint object with zero of red, green, and blue
	 * @param none
	 */
	public Paint ()
	{
		this(0,0,0);
	}//end default constructor Paint()

	/**
	 * constructs a Paint object using the given double values for red, green and blue
	 * the parameters are evaluated in this order: first -> red, second -> green, third -> blue
	 * no instance variable can be set to less than zero using this constructor, so it sets the intended field to zero upon being called with a negative value
	 * @param double qRed - the quantity of red paint in litres
	 * @param double qGreen - the quantity of green paint in litres
	 * @param double qBlue - the quantity of blue paint in litres
	 */
	public Paint (double qRed, double qGreen, double qBlue)
	{
		//check for qRed parameter being less than 0 here: if it is less, print an error statement and set to zero, otherwise just set this.qRed normally
		if (qRed < 0)
		{
			this.qRed = 0;
			System.out.println("Failure to initialize amount of red paint to " + qRed + ". It has been set to zero.");
		}
		else
		{
			this.qRed = qRed;
		}//end if

		if (qGreen < 0)
		{
			this.qGreen = 0;
			System.out.println("Failure to initialize amount of green paint to " + qGreen + ". It has been set to zero.");
		}
		else
		{
			this.qGreen = qGreen;
		}//end if

		if (qBlue < 0)
		{
			this.qBlue = 0;
			System.out.println("Failure to initialize amount of blue paint to " + qBlue + ". It has been set to zero.");
		}
		else
		{
			this.qBlue = qBlue;
		}//end if
	}//end constructor Paint(double, double, double)

	/**
	 * constructs a Paint object which has the same amount of red, green, and blue as the given Paint object
	 * @param Paint copy - Paint object to copy
	 */
	public Paint (Paint copy)
	{
		this(copy.getRed(), copy.getGreen(), copy.getBlue());
	}//end constructor Paint(Paint)

	/**********		*
	 * Get methods
	 **********		*/
	
	/**
	 * returns the held quantity of red paint (litres)
	 * @param none
	 * @return double qRed - amount of red
	 */
	public double getRed ()
	{
		return this.qRed;
	}//end member getRed
	
	/**
	 * returns the held amount of green paint
	 * @param none
	 * @return double qGreen - amount of green
	 */
	public double getGreen ()
	{
		return this.qGreen;
	}//end member getGreen

	/**
	 * returns the amount of blue paint
	 * @param none
	 * @return double qBlue - amount of blue
	 */
	public double getBlue ()
	{
		return this.qBlue;
	}//end member getBlue

	/**********		*
	 * Set methods
	 **********		*/

	/**
	 * attempts to set the quantity of red paint, but checks for and does not set negative amounts
	 * @param double quantity - new amount
	 * @return void
	 */
	public void setRed (double quantity)
	{
		if (quantity < 0)
			System.out.println("Failure to modify amount of red paint (must be at least zero). It has not changed from " + qRed);
		else
			this.qRed = quantity;
	}//end member setRed

	/**
	 * attempts to set the quantity of green paint, but checks for and does not set negative amounts
	 * @param double quantity - new amount
	 * @return void
	 */
	public void setGreen (double quantity)
	{
		if (quantity < 0)
			System.out.println("Failure to modify amount of green paint (must be at least zero). It has not changed from " + qGreen);
		else
			this.qGreen = quantity;
	}//end member setGreen

	/**
	 * attempts to set the quantity of blue paint, but checks for and does not set negative amounts
	 * @param double quantity - new amount
	 * @return void
	 */
	public void setBlue (double quantity)
	{
		if (quantity < 0)
			System.out.println("Failure to modify amount of blue paint (must be at least zero). It has not changed from " + qBlue);
		else
			this.qBlue = quantity;
	}//end member setBlue
	
	/**********		*
	 * Instance methods
	 **********		*/

	/**
	 * adds all three paint colour quantities together and returns the combined amount of paint
	 * @param none
	 * @return double - the total amount of paint contained
	 */
	public double totalAmt ()
	{
		return qRed + qGreen + qBlue;
	}//end member totalAmt

	/**
	 * compares another Paint object with the instance object:
	 * returns true if there is the same amount of every colour,
	 * false if the other Paint object is null or otherwise
	 * @param Paint compare - Paint object to be compared
	 * @return boolean - true if the objects are equivalent (they have the same of each colour), false otherwise
	 */
	public boolean equals (Paint compare)
	{
		if (compare != null)
			return (
				this.qRed == compare.qRed &&
				this.qBlue == compare.qBlue &&
				this.qGreen == compare.qGreen
			       );
		else
			return false;
	}//end member equals

	/**
	 * compares another Paint object with the instance object,
	 * returns true if the other object's ratio of red : green : blue paint if equal to the invoked object's ratio,
	 * false if the other Paint object is null or otherwise
	 * @param Paint compare - Paint object to be compared
	 * @return boolean - true if the compared object's red : green : blue ratio (percentage composition) is the same as the invoked object's, false otherwise
	 */
	public boolean sameColour (Paint compare)
	{
		//if the compared object is not null, calculate the red : total, green : total, and blue : total ratios (where total is the total amount of paint)
		//checks red : total ratio, green : total, and blue : total ratios, and seeing if they are all equal
		//if two completely empty Paint objects are compared, the function returns false (behavior is undefined as of the assignment description)
		if (compare != null)
		{
			//compare the ratios to see if they are the same (red to green and red to blue must both be equal)
			return (
				this.qRed / this.totalAmt() == compare.qRed / compare.totalAmt() &&
				this.qGreen / this.totalAmt() == compare.qGreen / compare.totalAmt() &&
				this.qBlue / this.totalAmt() == compare.qBlue / compare.totalAmt()
			       );
		}
		else
		{
			return false;
		}//end if
	}//end member sameColour

	/**
	 * calculates the total cost of the Paint object
	 * @param none
	 * @return double - a double representing the total cost in dollars of all ordered red, green, and blue paint
	 */
	public double totalCost ()
	{
		/**
		 * uses the constants in this class which define the price per litre of each colour, multiplies those with the stored quantities, and sums them
		 * 'Paint' and 'this' invocations are redundant, but are used for clarification
		 */
		return (
			Paint.RED_PRICE * this.qRed +
			Paint.GREEN_PRICE * this.qGreen +
			Paint.BLUE_PRICE * this.qBlue
		       );
	}//end member totalCost

	/**
	 * creates a String out of the Paint object which contains the amount of each colour, the amount of all paint combined, and the total price
	 * and then it wraps it in some nice formatting, every number is displayed to two decimals
	 * @param none
	 * @return String - a String with the value of amount of red, green, and blue paint, the total paint, and the price of all paints combined
	 */
	public String toString ()
	{
		//constructs the String using the format method from the String class
		String thisAsString = 
			String.format(
				"%.2fL red, %.2fL green, and %.2fL blue can create %.2fL of paint at a total cost of $%.2f",
				this.qRed,
				this.qGreen,
				this.qBlue,
				this.totalAmt(),
				this.totalCost()
				);
		return thisAsString;
	}//end member toString

	/**********		*
	 * Class methods
	 **********		*/

	/**
	 * private method which tries to read a double repeatedly until the user inputs a valid String which can be converted
	 * every time it fails to read a double, the user will be prompted again with a set message
	 * this is necessary to ensure that the Paint.request() method below does not allow the user to crash programs
	 * @param Scanner input - the Scanner object which lines are pulled from, until a valid double is found
	 * @param String reprompt - the String which will be displayed in the console every time the user enters a line which cannot be converted into a double
	 * @return double - the first valid parsed double that the user has entered
	 */
	private static double safeReadDouble (Scanner input, String reprompt)
	{
		//the String to be read from the Scanner
		String userInput;

		//used as a flag to indicate whether a double has been successfully found
		boolean foundValidDouble = true;

		//read a line from the Scanner, then run it through the following try/catch block
		userInput = input.nextLine();
		
		//try to parse the line read, and catch an error stating that it is not in the correct number format by setting foundValidDouble to false
		try
		{
			Double.parseDouble(userInput);
		}//end try
		catch (NumberFormatException except)
		{
			foundValidDouble = false;
		}//end catch(NumberFormatException)

		//if a double has been found, return it; otherwise, run this procedure again until a double is found (by calling it recursively)
		if (foundValidDouble)
		{
			return Double.parseDouble(userInput);
		}
		else
		{
			//display the prompt to remind the user that their input was not valid
			System.out.println(reprompt);

			return safeReadDouble(input, reprompt);
		}//end if
	}//end static member safeReadDouble

	/**
	 * class method to prompt an interactive console interface for users, where a Paint object is returned based on the user's specifications
	 * the user enters doubles at the prompts for red, green, and blue in that order
	 * NOTE: this method allows the user to enter negative amounts, although these amounts will be treated as invalid by the invoked Paint constructor
	 * in the event of negative amounts entered, the constructor displays a message to the console about what happened and sets the fields to zero instead
	 * @param none
	 * @return Paint - a Paint object which contains exactly the amount of each colour as ordered by the user
	 */
	public static Paint request ()
	{
		Scanner input = new Scanner(System.in);

		//stores amount of red, green, and blue paint wanted by the user
		double red, green, blue;

		//prompt and read the value for red
		System.out.println("Enter the amount of red.");
		red = Paint.safeReadDouble(input, "You have entered an invalid decimal number. Try again: enter the amount of red.");

		//prompt and read the value for green
		System.out.println("Enter the amount of green.");
		green = Paint.safeReadDouble(input, "You have entered an invalid decimal number. Try again: enter the amount of green.");

		//prompt and read the value for blue
		System.out.println("Enter the amount of blue.");
		blue = Paint.safeReadDouble(input, "You have entered an invalid decimal number. Try again: enter the amount of blue.");

		//creates a new Paint object and immediately returns it, using the user's orders as initial values for the colour fields
		return new Paint(red, green, blue);
	}//end static member request

	/**
	 * calculates the cost of a certain quantity of a certain colour of paint
	 * prices are dictated by the constants RED_PRICE, BLUE_PRICE, and GREEN_PRICE (price per litre)
	 * @param String colour - a String which should be "red", "green", or "blue"
	 * @param double amount - the amount of paint in litres
	 * @return double - the cost of the paint in dollars, 0 if the String passed to the function is not a valid colour
	 */
	public static double cost (String colour, double amount)
	{
		//straightforward calculation for red, green, and blue paint: multiply amount of litres by price per litre to get the total price
		if (colour.equals("red"))
		{
			return RED_PRICE * amount;
		}
		else if (colour.equals("green"))
		{
			return GREEN_PRICE * amount;
		}
		else if (colour.equals("blue"))
		{
			return BLUE_PRICE * amount;
		}
		//if an invalid String is used to denote colour, then the program will print that it is not a colour
		//since it is not a colour, the program will return 0 (it will cost nothing to buy what doesn't exist)
		else
		{
			System.out.println("Failure to calculate cost. " + colour + " is not a valid colour.");
			return 0;
		}//end if
	}//end static member cost

}//end class Paint