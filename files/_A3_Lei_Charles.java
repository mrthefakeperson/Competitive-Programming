/**
 * a Swing program which draws a house, sun, and sky, with other associated features
 * provides various class templates to make drawing figures and managing them easier
 * the GUI scales to fit the window, and the sun and sky are dynamic (dependant on system time)
 *
 * created on 28/10/2015, for Ms. Tam's ICS4U1 class
 * @author Charles Lei
 */
//GUI imports
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

//audio playing imports
import java.io.*;
import sun.audio.*;

/**
 * main class to run the GUI
 * @author Charles Lei
 */
public class A3_Lei_Charles extends JFrame
{
	/***************		*
	 * constructors
	 ***************		*/

	/**
	 * creates the window with the title, also sets the dimensions to 800 by 600 and constructs the drawable JPanel
	 * @param String title - the title of the window
	 */
	public A3_Lei_Charles(String title)
	{
		super(title);

		//create the picture, set its size and add it
		DisplayPicture picture = new DisplayPicture();
		picture.setPreferredSize(new Dimension(800, 600));
		this.add(picture);
		
		//make the frame visible and pack it to the correct size
		this.pack();
		this.setVisible(true);
	}//end constructor (String)

	/***************		*
	 * class methods
	 ***************		*/

	/**
	 * runs the program (main entrypoint method)
	 * @param String[] args - string array passed to the program
	 */
	public static void main(String[] args) throws IOException
	{
		new A3_Lei_Charles("House with Sun and Sky");
	}//end static member main

}//end class A3_Lei_Charles

/**
 * class to inherit JPanel and draw the picture
 * @author Charles Lei
 */
class DisplayPicture extends JPanel
{
	/***************		*
	 * class variables
	 ***************		*/

	//keeps track of how much the screen has been stretched widthwise, as a percentage value
	private static double scaleX;

	//keeps track of how much the screen has been stretched lengthwise, as a percentage value
	private static double scaleY;

	//Graphics variable to be used by all drawing methods (retrieved by the overridden paintComponent method)
	private static Graphics grfx;

	//number used for all random activities, generated once upon being run
	private static int randomSeed;

	/***************		*
	 * constructors
	 ***************		*/

	/**
	 * creates the picture and populates the random generation seed
	 * @param none
	 */
	public DisplayPicture()
	{
		//call the base constructor
		super();

		//add onto it by generating a random number less than 10^9, which is used to make all random decisions of the program
		randomSeed = (int)(Math.random() * 1000000000);
	}//end default constructor ()

	/***************		*
	 * class methods
	 ***************		*/

	/**
	 * draws the house in the picture
	 * @param int leftX - the x coordinate of the top left corner of where this will be drawn
	 * @param int topY - the y coordinate of the top left corner of where this will be drawn
	 * @return void
	 */
	private static void drawHouse(int leftX, int topY)
	{
		//the house is a pencil shape for the main structure, with a polygonal roof on top, a chimney, rectangular windows, and a rectangular door

		//the main structure
		Shape mainStructure = new Shape(
						new Color(155, 125, 70),
						new int[]{0, 60, 120, 120, 0},
						new int[]{40, 0, 40, 160, 160}
					);
		//the roof
		Shape roof = new Shape(
					new Color(50, 50, 50),
					new int[]{-10, 60, 130, 140, 60, -20},
					new int[]{50, 0, 50, 40, -20, 40}
				);
		//the chimney (a rectangle intersecting the roof)
		Shape chimney = new Shape(
						new Color(50, 50, 50),
						new int[]{20, 50, 50, 20},
						new int[]{50, 50, -20, -20}
					);
		//the windows (two of them)
		Shape window1 = new Shape(
						new Color(50, 50, 50),
						new int[]{10, 55, 55, 10},
						new int[]{60, 60, 100, 100}
					);
		Shape window2 = new Shape(
						new Color(50, 50, 50),
						new int[]{65, 110, 110, 65},
						new int[]{35, 60, 100, 100}
					);
		//the gaps in the windows (two per window)
		Shape window1GapA = new Shape(
						new Color(120, 190, 120),
						new int[]{15, 30, 30, 15},
						new int[]{65, 65, 95, 95}
					);
		Shape window1GapB = new Shape(
						new Color(120, 190, 120),
						new int[]{35, 50, 50, 35},
						new int[]{65, 65, 95, 95}
					);
		Shape window2GapA = new Shape(
						new Color(120, 190, 120),
						new int[]{70, 85, 85, 70},
						new int[]{48, 55, 95, 95}
					);
		Shape window2GapB = new Shape(
						new Color(120, 190, 120),
						new int[]{90, 105, 105, 90},
						new int[]{58, 65, 95, 95}
					);
		//the door
		Shape door = new Shape(
					new Color(105, 80, 60),
					new int[]{70, 105, 105, 70},
					new int[]{110, 110, 160, 160}
				);
		Ellipse doorknob = new Ellipse(
						new Color(80, 30, 30),
						97, 130,
						5, 5
					);

		//put it all together
		SingleFigure[] house =
		 {
			mainStructure,
			roof,
			chimney,
			window1, window1GapA, window1GapB,
			window2, window2GapA, window2GapB,
			door, doorknob
		 };

		//create a Group out of the array, and draw all the shapes
		(new Group(house, leftX, topY, scaleX, scaleY)).draw(grfx);
	}//end static member drawHouse

	/**
	 * draws the sky
	 * @param int leftX - the x coordinate of the top left corner of where this will be drawn
	 * @param int topY - the y coordinate of the top left corner of where this will be drawn
	 * @param Color skyColor - the colour of the sky (a function of sin(time) for all three RGB values)
	 * @return void
	 */
	private static void drawSky(int leftX, int topY, Color skyColor)
	{
		//sky (rectangle)
		int skyX1 = 0, skyX2 = 700, skyY1 = 0, skyY2 = 500;

		Shape[] sky =
		 {
			new Shape(skyColor, new int[]{skyX1, skyX2, skyX2, skyX1}, new int[]{skyY1, skyY1, skyY2, skyY2})
		 };

		//draw the sky
		(new Group(sky, leftX, topY, scaleX, scaleY)).draw(grfx);
	}//end static member drawSky

	/**
	 * draws the ground
	 * @param int leftX - the x coordinate of the top left corner of where this will be drawn
	 * @param int topY - the y coordinate of the top left corner of where this will be drawn
	 * @return void
	 */
	private static void drawGround(int leftX, int topY)
	{
		//ground is a rectangle spanning the lower part of the screen
		int groundX1 = 0, groundX2 = 700, groundY1 = 260, groundY2 = 500;

		//get the colour (a shade of green)
		Color groundColor = new Color(40, 180, 80);

		//create the ground (a rectangle with the created colour)
		Shape[] ground =
		 {
			new Shape(
					groundColor,
					new int[]{groundX1, groundX2, groundX2, groundX1},
					new int[]{groundY1, groundY1, groundY2, groundY2}
				)
		 };

		//draw it
		(new Group(ground, leftX, topY, scaleX, scaleY)).draw(grfx);
	}//end static member drawGround

	/**
	 * the sun is drawn in the method below (bright circle in the sky with a face)
	 * @param int leftX - the x coordinate of the top left corner of where this will be drawn
	 * @param int topY - the y coordinate of the top left corner of where this will be drawn
	 * @return void
	 */
	private static void drawSun(int leftX, int topY)
	{
		//bright circle which is the outside of the sun
		Ellipse face = new Ellipse(Color.yellow, 0, 0, 60, 60);

		//eyes with pupils
		Ellipse eye1 = new Ellipse(Color.white, 5, 10, 15, 15);
		Ellipse eye2 = new Ellipse(Color.white, 40, 10, 15, 15);

		Ellipse pupil1 = new Ellipse(Color.black, 10, 15, 7, 7);
		Ellipse pupil2 = new Ellipse(Color.black, 45, 15, 7, 7);

		//screaming mouth below: is a function of the sun's height (a function of sine); the higher the sun is, the slower the mouth moves
		
		//the change in the position of each corner of the sun's mouth (it has six vertices)
		int changeInPosition = 5 - topY % 10;
		Shape mouth = new Shape(
					Color.black,
					new int[]{12 + changeInPosition, 15, 45 + changeInPosition, 48 - changeInPosition, 45, 15 - changeInPosition},
					new int[]{38, 30 + changeInPosition, 30 + changeInPosition, 38, 45 - changeInPosition, 45 - changeInPosition}
				);
		
		//assemble the sun
		SingleFigure[] fullSun =
		 {
			face,
			eye1, eye2,
			pupil1, pupil2,
			mouth
		 };
		
		//draw the whole thing
		(new Group(fullSun, leftX, topY, scaleX, scaleY)).draw(grfx);
	}//end static member drawSun

	/**
	 * returns a new Group which represents a cob, where (0, 0) is the centre of the cob
	 * many items are drawn "on the cob", so this method is called a few times
	 * other methods dilate the returned array, shift it around, flip it, etc. and draw things on the cob
	 * @param none
	 * @return SingleFigure[] - array of SingleFigure objects which together form a cob (to be used in a Group constructor with desired other values)
	 */
	private static SingleFigure[] onACob()
	{
		//a cob consists of a splitting stem, leaves, and two cobs (one horizontal, one vertical)
		
		//stem
		Shape stem = new Shape(
					//dark green
					new Color(0, 150, 30),
					//six sided polygon, shaped like a bent straw
					new int[]{0, 10, 20, 45, 45, 15},
					new int[]{0, 0, -25, -50, -55, -30}
				);
		Shape splitStem = new Shape(
					//darker green
					new Color(0, 130, 20),
					//six sided polygon, shaped like a bent straw
					new int[]{0, 5, 5, 10, 15, 15, 10},
					new int[]{0, -35, -60, -55, -60, -32, 0}
				);
		//leaves:

		//left leaf
		Shape leaf1 = new Shape(
					//dark green
					new Color(0, 150, 30),
					new int[]{0, 2, 0, -5, -7, -4},
					new int[]{0, -5, -10, -12, -8, -3}
				);
		//right leaf
		Shape leaf2 = new Shape(
					new Color(0, 150, 30),
					new int[]{10, 20, 35, 25},
					new int[]{0, -7, -9, -3}
				);
		//cob (yellow ellipse)
		Ellipse cob = new Ellipse(Color.yellow, 35, -60, 55, 25);

		//assemble the cob
		SingleFigure[] entireCob = 
		 {
			stem, splitStem,
			leaf1, leaf2,
			cob
		 };

		//just return the array of parts which make up the cob, without any dilations (other functions which call this one will transform it)
		for (SingleFigure figure : entireCob)
		{
			//-62 x, +48 y is used on every part to make the centre of yellow part of the cob at (0, 0)
			figure.offset(-62, 48);
		}//end for

		return entireCob;
	}//end static member onACob

	/**
	 * draws the flowers in the picture (there are a few of them)
	 * returned as an array of Ellipse, so that it can be transformed and dilated later
	 * @param int randomNumber - value to decide which colour to draw the petals
	 * @return Ellipse[] - array of Ellipse objects which together form a flower (to be used in a Group constructor with desired other values)
	 */
	private static Ellipse[] makeFlower(int randomNumber)
	{
		//selection of petal colours, to be chosen at random
		Color[] petalColour =
			 {
				new Color(200, 40, 70),
				new Color(150, 150, 20),
				new Color(150, 100, 100)
			 };
		//choose one of the colours (an index from zero to two)
		int colourChosen = (randomNumber + randomSeed) % 3;

		//flower petals (five elliptical objects, not too complex so declared anonymously as part of an array)
		Ellipse[] flower =
		 {
			//petals of the flowers are all the chosen colour, arranged as four circles in a square
			new Ellipse(petalColour[colourChosen], 0, 0, 10, 10),
			new Ellipse(petalColour[colourChosen], 10, 10, 10, 10),
			new Ellipse(petalColour[colourChosen], 0, 10, 10, 10),
			new Ellipse(petalColour[colourChosen], 10, 0, 10, 10),

			//the centre of the flower is always white
			new Ellipse(Color.white, 5, 5, 10, 10)
		 };

		//return the array representing the flower
		return flower;

	}//end static member makeFlower

	/**
	 * draws the flowers on a cob by putting flower() and onACob() together
	 * @param int leftX - the x coordinate of the top left corner of where this will be drawn
	 * @param int topY - the y coordinate of the top left corner of where this will be drawn
	 * @param double hStretch - horizontal stretch factor for whole flower
	 * @param double vStretch - vertical stretch factor for whole flower
	 * @return void
	 */
	private static void drawFlowersOnACob(int leftX, int topY, double hStretch, double vStretch)
	{
		//flowers on a cob consists of a cob and flowers
		
		//get the cob
		SingleFigure[] cob = onACob();

		//get three flowers (each flower must have a different colour, but which colour belongs to which flower is decided randomly)
		Ellipse[][] flowers = 
		 {
			makeFlower(0), makeFlower(1), makeFlower(2)
		 };

		//put them together
		Group[] entireFlower =
		 {
			//the corn cob
			(new Group(cob, 0, 0, 1, 1)),

			//the three flowers
			(new Group(flowers[0], -10, -3, 1, 1)),
			(new Group(flowers[1], -30, -10, 1, 1)),
			(new Group(flowers[2], 10, -15, 1, 1))
		 };

		//iterate through all four parts of the flower, and apply scaling and drawing operations to each
		for (Group component : entireFlower)
		{
			//scale by the factor specified using params hStretch and vStretch
			component.scale(hStretch, vStretch);

			//put it on the desired part of the screen
			component.offset(leftX + 62, topY - 48);

			//now scale it again to be flexible with the window
			component.scale(scaleX, scaleY);

			//draw
			component.draw(grfx);
		}//end for
	}//end static member drawFlowersOnACob

	/**
	 * creates the trees in the picture
	 * returned as an array of SingleFigure, so that it can be transformed and dilated later
	 * @param randomNumber - value to decide which colour to draw the leaves
	 * @return - array of SingleFigure objects which together form a flower (to be used in a Group constructor with desired other values)
	 */
	private static SingleFigure[] makeTree(int randomNumber)
	{
		//a tree has a trunk and a puffy green collection of leaves
		
		//the trunk
		Shape trunk = new Shape(
					//brown
					new Color(150, 150, 150),
					//trunk is a five sided figure (a trapezoid with a V in the top side)
					new int[]{-10, 10, 7, 0, -7},
					new int[]{35, 35, -10, 0, -10}
				);
		//the leaves

		//a selection of summer and autumn tinges of green for the leaves
		Color[] leafColour =
			 {
				new Color(100, 180, 20),
				new Color(130, 150, 10),
				new Color(70, 210, 40)
			 };
		//colours are selected at random, using an index from zero to two
		int colourChosen = (randomNumber + randomSeed) % 3;

		//make five leaves with the selected colour in a circular pattern
		Ellipse[] leaves =
		 {
			//directly above the trunk
			new Ellipse(leafColour[colourChosen], -18, -35, 45, 25),

			//top left of the trunk
			new Ellipse(leafColour[colourChosen], -40, -25, 45, 25),

			//top right the trunk
			new Ellipse(leafColour[colourChosen], 0, -30, 45, 25),

			//bottom left of the trunk
			new Ellipse(leafColour[colourChosen], -30, -15, 45, 25),

			//bottom right of the trunk
			new Ellipse(leafColour[colourChosen], -7, -15, 45, 25)
		 };

		//put it all together, leaves go behind the trunk
		SingleFigure[] entireTree =
		 {
			leaves[0], leaves[1], leaves[2], leaves[3], leaves[4],
			trunk
		 };

		//return the array representing the tree
		return entireTree;

	}//end static member makeTree

	/**
	 * draws trees on a cob by combining makeTree() and onACob()
	 * @param int leftX - the x coordinate of the top left corner of where this will be drawn
	 * @param int topY - the y coordinate of the top left corner of where this will be drawn
	 * @return void
	 */
	private static void drawTreesOnACob(int leftX, int topY)
	{
		//get the cob
		SingleFigure[] cobComponents = onACob();

		//construct the Group representing the cob
		Group cob = new Group(cobComponents, 0, 0, 1, 1);

		//stretch it to about three times its original dimensions
		//the negative parameter here indicates a horizontal reflection of the figure
		cob.scale(-3.2, 3.5);

		//put it at the desired part of the screen
		cob.offset(leftX + 64, topY - 48);

		//scale it to the dimensions of the screen
		cob.scale(scaleX, scaleY);

		//draw the cob
		cob.draw(grfx);

		//randomly generate trees with a fixed distance in between of 25 units
		//there will be seven randomly generated trees, lining the giant cob plant
		for (int e = 1; e <= 151; e += 25)
		{
			//make a tree, with an arbitrarily selected colour scheme
			SingleFigure[] treeComponents = makeTree(e / 25);

			//construct it as a Group of drawable figures so that we can stretch and move it around
			Group tree = new Group(treeComponents, 0, 0, 1, 1);

			//make the lower right corner (0, 0)
			tree.offset(10, -35);

			//select a random size for the tree, some trees will be a little larger than others
			tree.scale(0.5 + (randomSeed % e / 4.0 / (double)e), 0.35 + (randomSeed % e / 4.0 / (double)e));

			//decide to flip it or not (every odd numbered tree is flipped)
			//also, change its position a little based on the curve of the cob
			if (e / 25 % 2 == 0)
			{
				//negative y stretch indicates a vertical flip with no other transformations
				tree.scale(1, -1);

				//function: e -> 65 - (e - 75)^2 / 250 distributes trees so that trees in the centre bulge down
				tree.offset(0, 65 - (e - 75) * (e - 75) / 250);
			}
			else
			{
				//function: e -> (e - 75)^2 / 250 distributes trees so that trees in the centre bulge up
				tree.offset(0, (e - 75) * (e - 75) / 250);
			}//end if

			//make it the proper position
			tree.offset(leftX + e - 20, topY - 80);

			//and the proper size for the screen size
			tree.scale(scaleX, scaleY);

			//finally, draw it
			tree.draw(grfx);
		}//end for
	}//end static member drawTreesOnACob

	/**
	 * overrides the paint method which draws the entire screen
	 * @param Graphics retrievedGrfx - graphics object for drawing
	 * @return void
	 * @override
	 */
	public void paintComponent(Graphics retrievedGrfx)
	{
		//update graphics object (used by many static methods within this class)
		grfx = retrievedGrfx;

		//get current time
		long currentTime = System.currentTimeMillis();

		//the screen is 600 units wide, 400 high (the Group class scales all of its stored shapes)
		//offsets are also affected by the scale which makes it possible to express all dimensions as (x < 600, y < 400)
		//and still have them resize easily to fit the screen
		Rectangle screenSize = this.getBounds();

		//by dividing the retrieved dimensions by the default window size, we get a percentage value of each dimension
		//which is a multiplier for each drawn object's dimensions
		scaleX = screenSize.width / 600.0;
		scaleY = screenSize.height / 400.0;

		//draw background elements (horizon, sky, sun)

		//get the sun's position in the sky as a function of sin(current time)
		int sunHeight = 200 + (int)(Math.sin(currentTime / 5000.0) * 200);

		//the colour of the sky is a function of sin(current time), so related to the sun's height
		//as the sun gets higher, the sky becomes more red, and as it gets lower, it becomes darker and more blue
		Color skyColor = new Color(
						//red decreases as the sun gets higher
						(int)(250 - sunHeight * 0.25),
						//green increases as the sun get higher
						(int)(80 + sunHeight * 0.25),
						//blue increases substantially as the sun gets higher
						(int)(50 + sunHeight * 0.5)
					);
		//draw the sky
		drawSky(0, 0, skyColor);

		//sun is in front of sky, behind ground
		//note that it starts at a random x-position in the sky
		drawSun(50 + randomSeed % 20, sunHeight);

		//play the scream sound effect which presumably comes from the sun (the scream sound effect is played around once per second)
		if (currentTime % 1000 < 50)
		{
			//catch the possible IOException from the file not existing
			try
			{
				//read from the file name "scream_male.wav"
				FileInputStream noiseStream = new FileInputStream("scream_male.wav");
				AudioStream scream = new AudioStream(noiseStream);

				//start the sound
				AudioPlayer.player.start(scream);
			}
			catch (IOException ex)
			{
				//error prompt for file not existing (Java.io.IOException)
				System.out.println("ERROR: could not find the audio file");
			}//end try/catch
		}//end if

		//draw the ground
		drawGround(0, 0);

		//draw the house
		drawHouse(150, 150);

		//draw flowers (on a cob); integer values are arbitrarily selected to randomly distribute the flowers
		drawFlowersOnACob(30, 300, 0.35, 0.45);
		drawFlowersOnACob(320, 305, 0.35, 0.4);
		drawFlowersOnACob(20, 310, 0.55, 0.5);
		drawFlowersOnACob(50, 315, 0.5, 0.4);
		drawFlowersOnACob(50, 315, 0.4, 0.45);
		drawFlowersOnACob(20, 360, 0.85, 0.8);
		drawFlowersOnACob(50, 370, 0.6, 0.65);
		drawFlowersOnACob(250, 370, 0.6, 0.65);

		//this one is backwards
		drawFlowersOnACob(340, 375, -0.65, 0.7);

		//draw more flowers
		drawFlowersOnACob(230, 375, 0.65, 0.7);
		drawFlowersOnACob(-10, 380, 0.75, 0.8);
		drawFlowersOnACob(285, 380, 0.7, 0.7);
		drawFlowersOnACob(300, 385, 0.7, 0.6);
		drawFlowersOnACob(275, 385, 0.75, 0.75);
		drawFlowersOnACob(120, 400, 0.85, 0.8);
		drawFlowersOnACob(200, 415, 0.7, 0.6);

		//draw trees (on a cob)
		drawTreesOnACob(350, 200);
		
		//paint the next frame
		repaint();		
	}//end member paintComponent

}//end class DisplayPicture

/**
 * abstract class for other classes to inherit, represents a single drawable figure (circle, polygon, arc)
 * @author Charles Lei
 */
class SingleFigure
{
	/***************		*
	 * instance methods
	 ***************		*/

	/**
	 * inherited method for drawing
	 * @param Graphics grfx - the Graphics object with which to draw
	 * @return void
	 */
	public void draw(Graphics grfx)
	{
		//empty, other classes override this
	}//end member draw

	/**
	 * inherited method for x and y translation
	 * @param int x - the horizontal shift
	 * @param int y - the vertical shift
	 * @return void
	 */
	public void offset(int x, int y)
	{
		//empty, other classes override this
	}//end member offset

	/**
	 * inherited method for x and y stretching
	 * @param double scaleX - the horizontal stretch
	 * @param double scaleY - the vertical stretch
	 * @return void
	 */
	public void scale(double scaleX, double scaleY)
	{
		//empty, other classes override this
	}//end member scale
}//end class SingleFigure

/**
 * a shape class to store and draw polygons
 * @author Charles Lei
 */
class Shape extends SingleFigure
{
	/***************		*
	 * instance variables
	 ***************		*/

	//all of the x-coordinate values
	private int[] allX;

	//all of the y-coordinate values
	private int[] allY;

	//the colour to use for drawing
	private Color c;

	/***************		*
	 * constructors
	 ***************		*/

	/**
	 * creates a new Shape with given colour and sets of coordinate points
	 * @param Color c - the Color with which this will be drawn
	 * @param int[] allX - all of the x coordinates in an array
	 * @param int[] allY - all of the y coordinates in an array
	 */
	public Shape(Color c, int[] allX, int[] allY)
	{
		//set the colour
		this.c = c;

		//set the arrays for the x-coordinates and y-coordinates
		this.allX = allX;
		this.allY = allY;
	}//end constructor (Color, int[], int[])

	/***************		*
	 * instance methods
	 ***************		*/

	/**
	 * draws the polygon
	 * @param Graphics grfx - the Graphics object with which to draw
	 * @return void
	 * @override
	 */
	public void draw(Graphics grfx)
	{
		//set the colour to the one for this instance
		grfx.setColor(c);

		//create a polygon using the stored arrays and draw it
		grfx.fillPolygon(allX, allY, allX.length);
	}//end member draw

	/**
	 * slides every point of the polygon an equal amount, not changing the relative dimensions or angles, only its position on screen
	 * @param int xOffset - the horizontal shift
	 * @param int yOffset - the vertical shift
	 * @return void
	 * @override
	 */
	public void offset(int xOffset, int yOffset)
	{
		for (int e = 0; e < allX.length; e++)
		{
			//simple translation
			allX[e] += xOffset;
			allY[e] += yOffset;
		}//end for
	}//end member offset

	/**
	 * stretches every point about (0, 0)
	 * @param double scaleX - the horizontal stretch
	 * @param double scaleY - the vertical stretch
	 * @return void
	 * @override
	 */
	public void scale(double scaleX, double scaleY)
	{
		for (int e = 0; e < allX.length; e++)
		{
			//stretch all Xs and Ys about (0, 0)
			allX[e] *= scaleX;
			allY[e] *= scaleY;
		}//end for
	}//end member scale
}//end class Shape

/**
 * a class to draw ovals
 * @author Charles Lei
 */
class Ellipse extends SingleFigure
{
	/***************		*
	 * instance variables
	 ***************		*/

	//values for the oval being drawn
	//top left at (x, y)
	private int x;
	private int y;

	//width units wide
	private int width;

	//height units high
	private int height;

	//the colour for drawing
	private Color c;

	/***************		*
	 * constructors
	 ***************		*/

	/**
	 * creates a new Ellipse with given colour, position, and dimensions
	 * @param Color c - the Color with which this will be drawn with
	 * @param int x - lowest x coordinate
	 * @param int y - lowest y coordinate
	 * @param int width - width
	 * @param int height - height
	 */
	public Ellipse(Color c, int x, int y, int width, int height)
	{
		//set colour, x, y, width, and height in that order
		this.c = c;
		this.x = x;
		this.y = y;
		this.width = width;
		this.height = height;
	}//end constructor(Color, int, int, int, int)

	/***************		*
	 * instance methods
	 ***************		*/

	/**
	 * draws the ellipse
	 * @param Graphics grfx - the Graphics object with which to draw
	 * @return void
	 * @override
	 */
	public void draw(Graphics grfx)
	{
		//set the colour to the one for this instance
		grfx.setColor(c);

		//draw an oval (this is the Ellipse class)
		grfx.fillOval(this.x, this.y, this.width, this.height);
	}//end member draw

	/**
	 * slides the ellipse without changing its relative dimensions, only its position on screen
	 * @param int xOffset - the horizontal shift
	 * @param int yOffset - the vertical shift
	 * @return void
	 * @override
	 */
	public void offset(int xOffset, int yOffset)
	{
		//just perform a simple translation
		this.x += xOffset;
		this.y += yOffset;
	}//end member offset

	/**
	 * stretches the dimensions and position about (0, 0)
	 * @param double scaleX - the horizontal stretch
	 * @param double scaleY - the vertical stretch
	 * @return void
	 * @override
	 */
	public void scale(double scaleX, double scaleY)
	{
		//get the four corners of the oval to make it possible to stretch by negative values (flip)
		int x1 = this.x,
		    x2 = this.x + this.width,
		    y1 = this.y,
		    y2 = this.y + this.height;

		x1 *= scaleX;
		x2 *= scaleX;
		y1 *= scaleY;
		y2 *= scaleY;

		//look at the minimum of each coordinate to find new top left corner
		this.x = Math.min(x1, x2);
		this.y = Math.min(y1, y2);

		//subtract to find new dimensions
		this.width = Math.abs(x1 - x2);
		this.height = Math.abs(y1 - y2);
	}//end member scale
}//end class Ellipse

/**
 * a class for a group of shapes (polygons and ellipses)
 * they are all drawn at once, and can all be moved or stretched at once
 * @author Charles Lei
 */
class Group
{
	/***************		*
	 * instance variables
	 ***************		*/

	//array of SingleFigure, all elements contained will be drawn at once
	SingleFigure[] figures;

	/***************		*
	 * constructors
	 ***************		*/

	/**
	 * creates a Group out of either Shapes or Ellipses (they both inherit from SingleFigure)
	 * immediately offsets and scales, for convenience
	 * @param SingleFigure[] figures - an array of SingleFigures (Shapes and Ellipses, possibly mixed) which will be used to populate the group
	 * @param int xOffset - amount to move everything to the right by
	 * @param int yOffset - amount to move everything to up by
	 * @param double scaleX - horizontal stretch factor
	 * @param double scaleY - vertical stretch factor
	 */
	public Group(SingleFigure[] figures, int xOffset, int yOffset, double scaleX, double scaleY)
	{
		//assign the array of shapes' reference to this object
		this.figures = figures;
		
		//using the offsets provided as parameters, increment the x and y of each Shape object in the array
		//all the shapes will be drawn relative to the top left corner of (xOffset, yOffset)
		this.offset(xOffset, yOffset);

		//and scale them too
		this.scale(scaleX, scaleY);
	}//end constructor (SingleFigure[], int, int, double, double)

	/***************		*
	 * instance methods
	 ***************		*/

	/**
	 * draws all objects in the stored array
	 * @param Graphics grfx - the Graphics object with which to draw
	 * @return void
	 */
	public void draw(Graphics grfx)
	{
		for (SingleFigure figure : figures)
		{
			//draw the current figure in the array
			figure.draw(grfx);
		}//end for
	}//end member draw

	/**
	 * maps a slide transformation to all shapes contained
	 * @param int xOffset - the horizontal shift
	 * @param int yOffset - the vertical shift
	 * @return void
	 */
	public void offset(int xOffset, int yOffset)
	{
		for (SingleFigure figure : this.figures)
		{
			//translation operation
			figure.offset(xOffset, yOffset);
		}//end for
	}//end member offset

	/**
	 * maps a stretch transformation to all shapes contained
	 * @param double scaleX - the horizontal stretch
	 * @param double scaleY - the vertical stretch
	 * @return void
	 */
	public void scale(double scaleX, double scaleY)
	{
		for (SingleFigure figure : this.figures)
		{
			//stretch operation
			figure.scale(scaleX, scaleY);
		}//end for
	}//end member scale
}//end class Group