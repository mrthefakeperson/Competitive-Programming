/**
 * PigGame assignment
 * a GUI (swing) assignment which allows a user to play an interactive game
 * with a computer player making random decisions
 * involves rolling two dice, where players accumulate points unless they roll a one
 * rolling two ones results in no accumulated points, but 25 free points awarded
 * 
 * a persistent menu contains held money for user and computer, which is used to gamble on rounds
 * also contains the option to save during a game round or at the menu, and load from the menu
 *
 * created for Ms. Tam's ICS4U1 class on 13/11/15
 * @author Charles Lei
 */

import java.io.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

/**
 * wrapper class which contains the main method that starts the initial menu window
 *
 * @author Charles Lei
 */
public class A4_Lei_Charles
{
	/**
	 * wrapper main method, where the real entrypoint of the program is in the MenuWindow constructor
	 * @param String[] args - arguments passed to the program
	 * @return void
	 */
	public static void main(String[] args)
	{
		//start the menu, which contains a GUI for the user to play the game
		//starts both user and computer off with $200
		new MenuWindow(new GameInfo(200));
	}//end static member main
}//end class A4_Charles_Lei

/**
 * class which contains all relevant information and logic of the game
 * keeps track of accumulated points, turn, money and gambles for both local and global interactive games
 * implements the Serializable interface, to be easily saved
 * does almost all of the heavy lifting for the program; as such, saving an object of this class will save games entirely
 *
 * @author Charles Lei
 */
class GameInfo implements Serializable
{
	/**********			*
	 * constants
	 **********			*/
	 
	//final int COMPROLL: maximum number of times the computer chooses to roll every turn
	private static final int COMPROLL = 10;
	 
	/**********			*
	 * instance variables
	 **********			*/
	 
	/**********
	 * All variables are private unless stated otherwise.
	 *
	 * dictionary:
	 *	int playerMoney: stores amount of money held by player, in order to gamble
	 *	int computerMoney: stores amount of money held by computer, for gambling
	 *	int gamble: amount of money wagered on the current round
	 *	int goal: amount of points which will cause either the player or computer to win the game
	 *	boolean isPlayerTurn: stores: true for player's turn, false for computer's turn
	 *	int dice1:
	 *		number rolled for the left die; will display a die face or question marks if at default value
	 *		default is 0
	 *	int dice2:
	 *		number rolled for the right die; will display a die face or question marks if at default value
	 *		default is 0
	 *	int accumulatedPoints:
	 *		amount of points earned by current player before turn ends, which could be lost if a '1' is rolled
	 *		default is 0
	 *	int playerPoints:
	 *		total points earned by player this game
	 *		default is 0
	 *	int computerPoints:
	 *		total points earned by computer this game
	 *		default is 0
	 *	int computerRollsLeft:
	 *		number of rolls the computer still plans to make inside the gameOver
	 *		computer's turn can still end prematurely if it rolls a '1'
	 *		default is 0
	 *	boolean[] buttonStates:
	 *		from the PigGame class, stores for each button whether it is disabled or enabled
	 *		used to restore a saved game
	 *		default:
	 *		 {
	 *			 true,
	 *			 true,
	 *			 false,
	 *			 true,
	 *			 true
	 *		 }
	 **********/
	 
	private int playerMoney, computerMoney;
	
	private int gamble;
	private int goal;
	 
	private boolean isPlayerTurn = true;
	
	private int dice1 = 0, dice2 = 0;
	
	private int accumulatedPoints = 0;
	
	private int playerPoints = 0, computerPoints = 0;
	
	private int computerRollsLeft = 0;
	
	private boolean[] buttonStates =
	 {
		 true, 
		 true, 
		 false, 
		 true, 
		 true
	 };
	 
	/**********			*
	 * class variables
	 **********			*/
	 
	//static PrintWriter recap: used to write to 'pig.txt' (initialized upon construction of an instance of the class)
	private static PrintWriter recap;
	
	/**********			*
	 * constructors
	 **********			*/
	
	/**
	 * creates a new GameInfo object with the player's money and the computer's money set to an amount
	 * also initializes the PrintWriter object so that it writes to 'pig.txt'
	 * @param int startMoney - the initial amount of money in dollars
	 */
	public GameInfo(int startMoney)
	{
		//set both players' money to the initial value given
		this.playerMoney = startMoney;
		this.computerMoney = startMoney;
		
		//initialize the object used to write to pig.txt
		try
		{
			//pass "pig.txt" (path), and pass true to append to the file instead of deleting its contents
			FileWriter recapFile = new FileWriter("pig.txt", true);
			recap = new PrintWriter(recapFile);
		}
		catch (IOException ex)
		{
			//error prompt
			System.out.println("could not find pig.txt file: " + ex);
		}//end try/catch
	}//end constructor (int)
	
	/**********			*
	 * instance methods
	 **********			*/
	 
	//the following methods are used to perform the logic of the game
	
	/**
	 * given an array of JButtons, memorizes the state of each (whether each is enabled or not) to a stored array
	 * when the game is saved and needs to be restored, the state of each JButton will be restored as well
	 * restoration is used in member initializeGameWindow
	 * @param JButton[] buttons - the buttons whose states will be memorized
	 * @return void
	 */
	public void saveButtonStates(JButton[] buttons)
	{
		//copy the state of each button to the array, one for one
		for (int e = 0; e < 5; e++)
		{
			buttonStates[e] = buttons[e].isEnabled();
		}//end for
	}//end member saveButtonStates
	 
	/**
	 * takes gamble and goal values which indicate a user's bet and point limit for a particular game
	 * also resets all variables to the values they were at upon initial construction
	 * @param int gamble - integer representing a user's bet, in dollars
	 * @param int goal - integer representing the number of points at which the game will end
	 * @return void
	 */
	public void startGame(int gamble, int goal)
	{
		//write the game's start to a file
		recap.println("new game ->  gamble: " + gamble + "  goal: " + goal);
		recap.println();
		recap.println("The player goes first.");
		recap.flush();
		
		//set the gamble, set the goal
		this.gamble = gamble;
		this.goal = goal;
		
		//now, reset all variables to their defaults
		
		//player always goes first
		this.isPlayerTurn = true;
		
		//dice are unrolled (zeroes)
		this.dice1 = 0;
		this.dice2 = 0;
		
		//all points are reset
		this.accumulatedPoints = 0;
		this.playerPoints = 0;
		this.computerPoints = 0;
		
		//computer's planned number of rolls is also reset
		this.computerRollsLeft = 0;
		
		//the memorized states of all buttons, back to defaults
		this.buttonStates = new boolean[]{true, true, false, true, true};
	}//end member startGame
	 
	/**
	 * rolls two dice and stores their values, both individually and by adding them to an accumulator
	 * also detects if a '1' was rolled, and if so, returns true; otherwise false
	 * also writes some information about the roll to a file ('pig.txt')
	 * @param none
	 * @return boolean - true if a '1' was rolled, false otherwise
	 */
	public boolean nextRoll()
	{
		//if it is the computer's turn, deduct one from the number of times the computer is planning to roll
		if (!isPlayerTurn)
			computerRollsLeft--;
		
		//roll the dice
		this.dice1 = rollDice();
		this.dice2 = rollDice();
		
		//add the rolled values (now stored) to the accumulated points for the current player
		this.accumulatedPoints += this.dice1 + this.dice2;
		
		//detects if a roll is invalid (contains a '1')
		boolean invalidRoll = false;
		
		//different cases for both being '1', for one being '1', and also for the computer choosing to stop rolling
		if (dice1 == 1 && dice2 == 1)
		{
			invalidRoll = true;
			
			//for double ones, give the current player 25 accumulated points
			accumulatedPoints = 25;
		}
		else if (dice1 == 1 || dice2 == 1)
		{
			invalidRoll = true;
			
			//for a single one, give the current player no accumulated points
			accumulatedPoints = 0;
		}
		else if (!isPlayerTurn && computerRollsLeft == 0)
		{
			//also, if the computer has decided in advance to stop rolling at this time, then it will stop
			invalidRoll = true;
		}//end if
		
		//recap the results of the roll to the file
		recap.println("dice displays: " + dice1 + " and " + dice2);
		recap.println();
		recap.flush();
		
		//return true if the current player's turn must stop after this roll
		return invalidRoll;
	}//end member nextRoll
	
	/**
	 * ends the current turn by performing any concluding actions before switching the variable representing whose turn it is
	 * such actions include adding the accumulated points to someone's total score, resetting accumulated points,
	 * telling the computer how many times to roll if necessary, and writing a recap of the events to 'pig.txt'
	 * also returns whether it is the player's turn or not (communicates with surrounding methods)
	 * @param none
	 * @return boolean - true if it is the player's turn, false if it is the computer's turn
	 */
	public boolean endTurn()
	{
		//adds accumulated points to the party whose turn is being ended
		if (isPlayerTurn)
		{
			playerPoints += accumulatedPoints;
			
			//it is now the computer's turn: set the amount of times the computer plans to roll (random from 1 to COMPROLL)
			computerRollsLeft = (int)(Math.random() * COMPROLL) + 1;
			
			//recap the changes to the file
			recap.println("The player has received " + accumulatedPoints + " points.");
			recap.print("It is now the computer's turn. ");
		}
		else
		{
			computerPoints += accumulatedPoints;
			
			//recap the changes to the file
			recap.println("The computer has received " + accumulatedPoints + " points.");
			recap.print("It is now the player's turn. ");
		}//end if
		
		//recap the number of points held to the file
		recap.println("The player has " + playerPoints + " points. The computer has " + computerPoints + " points.");
		recap.println();
		recap.flush();
		
		//switch whose turn it is, reset number of accumulated points
		isPlayerTurn = !isPlayerTurn;
		accumulatedPoints = 0;
		
		//return a boolean representing whose turn it is
		return isPlayerTurn;
	}//end member endTurn
	
	/**
	 * detects if either the player or computer won (reached the point goal)
	 * if so, updates the money values so that the winner takes the value of the gamble from the loser
	 * and also writes to a file in event of someone winning
	 * @param none
	 * @return boolean - true if either the player or computer won, false otherwise
	 */
	public boolean someoneWon()
	{
		//detect if either player or computer has reached the goal
		if (playerPoints >= goal || computerPoints >= goal)
		{
			//detect which party has won
			if (playerPoints >= goal)
			{
				//transfer the gambled money to the winning party
				playerMoney += gamble;
				computerMoney -= gamble;
				
				//write the record of someone winning to a file
				recap.println("The player wins.");
				recap.flush();
			}
			else
			{
				//transfer the gambled money to the winning party
				computerMoney += gamble;
				playerMoney -= gamble;
				
				//write the record of someone winning to a file
				recap.println("The computer wins.");
				recap.flush();
			}//end if
			
			//true: someone did indeed win
			return true;
		}
		else
		{
			//false: no one won at the time this method was called
			return false;
		}//end if
	}//end member someoneWon
	
	//the following methods are used to construct other JFrame windows
	
	/**
	 * given a menu window (inherited from JFrame), finishes constructing it by modifying JComponents
	 * displays a message describing the current state of the game and detects if a round is in progress
	 * this method is called in the MenuWindow constructor
	 * @param MenuWindow menu - menu object which will have its components modified to match this GameInfo object
	 * @return void 
	 */
	public void initializeMenu(MenuWindow menu)
	{
		/**********
		 * NOTE: JComponents use HTML for text formatting
		 * markup symbols used:
		 *  <html></html> -> start/end html
		 *  <br> -> line break
		 *  <b></b> -> bold
		 *  <i></i> -> italics
		 *  <u></u> -> underline
		 *  <div style=\"\"> -> set text style as indicated in the quotes
		 *  <font size=\"\"></font> -> set text size as indicated in the quotes
		 **********/
		
		//stores a String which displays information about the game
		//such as the amount of money owned by either player (html, centred, bold)
		String message =
			String.format(
				//bolded header
				"<html><div style=\"text-align: center;\"><b><font size=\"16\">OINKOINKOINK</font><br>" + 
				//information about the money held
				"<font size=\"13\">Current game: <br><u>Player - $%d;    Computer - $%d </u></font><br><br>",
				//displays money of either player
				playerMoney, computerMoney
			);
			
		//detect if there is an unfinished round (no player has reached the goal yet)
		if (!(playerPoints >= goal) && !(computerPoints >= goal))
		{
			//if so, add a notice to the message and set the play button to 'continue round'
			message += "A round is in progress. <br>";
			menu.menuButtons[1].setText("continue round");
		}
		else
		{
			//otherwise, set the play button to 'play round'
			menu.menuButtons[1].setText("play round");
		}//end if
		
		//detect if either user or computer is out of money
		if (computerMoney <= 0)
		{
			//if the player won, add a message
			message += "<i><u>The player has won. The computer is out of money.<br> Start a new game?</i></u><br><br>";
			
			//disable the play round button and save game button, because the game is over
			menu.menuButtons[1].setEnabled(false);
			menu.menuButtons[2].setEnabled(false);
		}
		else if (playerMoney <= 0)
		{
			//if the computer won, add a message
			message += "<i>The computer has won. The player is out of money.<br> Start a new game?</i><br><br>";
			
			//disable the play round button and save game button, because the game is over
			menu.menuButtons[1].setEnabled(false);
			menu.menuButtons[2].setEnabled(false);
		}//end if
		
		//instructions to the user
		message += "Click the reset money button after entering an initial money value to reset money values.<br>";
		message += "Click the new round or continue round button to continue the current game.<br>";
		message += "Starting a new round allows you to gamble and play a dice game where the winner gets money.<br>";
		message += "If you or the computer runs out of money at any point, the game is over.<br><br>";
		message += "You can also save, load, or quit from this menu.<br>";
		message += "During the game, you can exit back to here or save during rounds.<br>";
		
		//append the end html tag (necessary for line breaks)
		message += "</b></html>";
		
		//display the message to the menu's JLabel (and set its font)
		menu.infoDisplay.setText(message);
		menu.infoDisplay.setFont(new Font("Trebuchet MS", Font.PLAIN, 12));
	}//end member initializeMenu
	
	/**
	 * finishes constructing a game window (inherited from JFrame, where the user plays the game)
	 * sets the public variables keeping track of whose turn it is, and changes the state of enabled buttons
	 * as a result, the game's display will match this GameInfo object completely
	 * this is called once inside the PigGame constructor
	 * @param PigGame gameWindow - the game class which needs to be modified to match this GameInfo object
	 * @return void
	 */
	public void initializeGameWindow(PigGame gameWindow)
	{
		//tell the game window whose turn it is
		gameWindow.isPlayerTurn = this.isPlayerTurn;
		
		//copy over the button states one for one
		for (int e = 0; e < 5; e++)
		{
			gameWindow.buttonControls[e].setEnabled(buttonStates[e]);
		}//end for
	}//end member initializeGameWindow
	
	/**
	 * finishes setting up a game over window (inherited from JFrame, user is displayed a summary of the game)
	 * displays a message in the window which contains a recap of the game
	 * this message is indicative of the state of the game currently
	 * called once in the GameOverWindow constructor
	 * @param GameOverWindow gameOver - the GameOverWindow to have its components modified to summarize this GameInfo object
	 * @return void
	 */
	public void initializeGameOver(GameOverWindow gameOver)
	{
		//contains message displayed to the user on a JLabel (html formatting, centred, italics)
		String message = "<html><div style=\"text-align: center;\"><i>The game has concluded.</i><br><br>";
		
		//detect if the player won, the computer won, or nobody won yet (user can save, quit game and resume later)
		if (playerPoints >= goal)
		{
			//player won: write down how much the player won with
			message +=
				String.format(
					"The player won with %d points, while the computer had %d.<br>The goal was %d.<br>",
					playerPoints, computerPoints, goal
					);
		}
		else if (computerPoints >= goal)
		{
			//computer won: write down how much the computer won with
			message +=
				String.format(
					"The computer won with %d points, while the player had %d.<br>The goal was %d.<br>",
					computerPoints, playerPoints, goal
					);
		}
		else
		{
			//nobody won: write down point values, and write that nobody has won yet
			message +=
				String.format(
					"The player has %d points, the computer has %d points.<br>%d is the goal, nobody won yet.<br>",
					playerPoints, computerPoints, goal
					);
		}//end if
		
		//prompt update on the money amounts
		message +=
			String.format(
				"<br>The gamble was %d.<br>The player now has %d dollars, while the computer has %d.<br>",
				gamble, playerMoney, computerMoney
			);
			
		//detect if anyone is out of money, and if so, display a short message
		if (playerMoney <= 0)
		{
			//user is out
			message += "<br><b><font size=\"30\">The player busts! </font></b><br>";
		}//end if
		if (computerMoney <= 0)
		{
			//computer is out
			message += "<br><b><font size=\"30\">The computer busts! </font></b><br>";
		}//end if
		
		//append end html tag for line breaks, set the display on the game over window to the message and use Treb. font
		message += "</html>";
		gameOver.displayMessage.setText(message);
		gameOver.displayMessage.setFont(new Font("Trebuchet MS", Font.PLAIN, 16));
	}//end member initializeGameOver
	
	//the following method is used to draw the contents of the game onto a GUI
	
	/**
	 * given a Graphics object to draw with, paints an image containing all relevant graphical info for the user to play the game
	 * such info includes dice (visual), total points on each side, current accumulated points, whose turn, and who won if anyone
	 * @param Graphics grfx - the Graphics object with which to draw
	 * @return void
	 */
	public void drawState(Graphics grfx)
	{
		//draw background (red/black colour scheme)
		//four trapezoids, two red, two gray
		grfx.setColor(new Color(100, 100, 100));
		grfx.fillPolygon(
			new int[]{0, 100, 400, 0},
			new int[]{0, 0, 300, 300},
			4
			);
		grfx.setColor(new Color(200, 50, 50));
		grfx.fillPolygon(
			new int[]{600, 100, 400, 600},
			new int[]{0, 0, 300, 300},
			4
			);
		grfx.fillPolygon(
			new int[]{25, 206, 330, 25},
			new int[]{150, 150, 275, 275},
			4
			);
		grfx.setColor(new Color(100, 100, 100));
		grfx.fillPolygon(
			new int[]{575, 165, 425, 575},
			new int[]{25, 25, 275, 275},
			4
			);
		
		
		//first section: write the status of the game (money, goal, points, gamble) onto the screen
		
		//header font
		grfx.setFont(new Font("Trebuchet MS", Font.BOLD, 16));
		
		//write the held money in green
		grfx.setColor(new Color(50, 190, 50));
		grfx.drawString("Player has $" + playerMoney, 30, 80);
		grfx.drawString("Computer has $" + computerMoney, 30, 105);
		
		//write the gamble
		grfx.drawString("$" + gamble + " is at stake", 30, 130);
		
		//write point summary in black
		grfx.setColor(Color.black);
		grfx.drawString("Point breakdown:", 30, 190);
		//player
		grfx.drawString("You have " + playerPoints + " points", 50, 215);
		//computer
		grfx.drawString("Computer has " + computerPoints + " points", 50, 240);
		//goal
		grfx.drawString("The game's point goal is " + goal, 30, 265);
		
		//next section: draw the dice
		
		//draw the dice, left and right
		drawDice(grfx, dice1, 330, 60);
		drawDice(grfx, dice2, 465, 60);
		
		//also write down the total if it wasn't self-explanatory enough
		//big font
		grfx.setFont(new Font("Trebuchet MS", Font.BOLD, 30));
		//dice1 value, dice2 value with + sign in between
		grfx.drawString("" + dice1, 365, 50);
		grfx.drawString("+", 425, 50);
		grfx.drawString("" + dice2, 500, 50);
		//total
		grfx.drawString("= " + (dice1 + dice2), 410, 190);
		
		//last section: write more immediate information for the game
		
		//smaller font
		grfx.setFont(new Font("Trebuchet MS", Font.BOLD, 13));
		
		//write onto the screen the active player's identity
		if (isPlayerTurn)
			grfx.drawString("It is the player's turn.", 385, 215);
		else
			grfx.drawString("It is the computer's turn.", 385, 215);
		
		//write how many points have been accumulated
		grfx.drawString("accumulated: " + accumulatedPoints + " points.", 390, 235);
		
		//did someone win? if so, put it on the screen
		//big font
		grfx.setFont(new Font("Trebuchet MS", Font.BOLD, 30));
		if (playerPoints >= goal)
			grfx.drawString("YOU WIN", 415, 263);
		if (computerPoints >= goal)
			grfx.drawString("YOU LOSE", 415, 263);
	}//end member drawState
	
	/**********			*
	 * class methods
	 **********			*/
	 
	/**
	 * returns a random int from 1 to 6 inclusive, to simulate a dice roll
	 * @param none
	 * @return int - random int from 1 to 6 inclusive
	 */
	private static int rollDice()
	{
		//get a random integer from 1 to 6, inclusive
		return (int)(Math.random() * 6) + 1;
	}//end static member rollDice
	
	/**
	 * given a Graphics object, a value to display, and two dimensions, draws a square face of a die with the given value
	 * value will be represented using number of dots on the face, in an ascetically pleasing manner
	 * @param Graphics grfx - Graphics object with which to draw
	 * @param int display - number of dots to display
	 * @param int xCorner - shift the whole die face this many pixels to the right
	 * @param int yCorner - shift the whole die face this many pixels down
	 * @return void
	 */
	private static void drawDice(Graphics grfx, int display, int xCorner, int yCorner)
	{
		//draw the outline for the die
		grfx.setColor(Color.black);
		grfx.fillRect(xCorner, yCorner, 100, 100);
		
		//draw a red die background
		grfx.setColor(Color.red);
		//but if the die face shows a one, flash it in rainbow colours instead
		if (display == 1)
		{
			//random values for RGB every frame create a glowing effect
			grfx.setColor(new Color((int)(Math.random() * 256), (int)(Math.random() * 256), (int)(Math.random() * 256)));
		}//end if
		grfx.fillRect(xCorner + 5, yCorner + 5, 90, 90);
		
		//draw the dots on the die face
		grfx.setColor(Color.black);
		//different cases for different numbers to be displayed
		switch (display)
		{
			//for zero, question marks will be drawn (0 indicates the die is unrolled at the start of a round)
			case 0:
				grfx.drawString("?????", xCorner + 20, yCorner + 40);
				
				break;
			//rolls 1: single dot in the middle
			case 1:
				/* ...
				   .1.
				   ...
				*/
				//drawn in respective order
				grfx.fillOval(xCorner + 40, yCorner + 40, 20, 20);
			
				break;
			//rolls 2: dot in the top left, bottom right
			case 2:
				/* 1..
				   ...
				   ..2
				*/
				grfx.fillOval(xCorner + 15, yCorner + 15, 20, 20);
				grfx.fillOval(xCorner + 65, yCorner + 65, 20, 20);
			
				break;
			//rolls 3: dot in the top left, middle, bottom right
			case 3:
				/* 1..
				   .2.
				   ..3
				*/
				grfx.fillOval(xCorner + 15, yCorner + 15, 20, 20);
				grfx.fillOval(xCorner + 40, yCorner + 40, 20, 20);
				grfx.fillOval(xCorner + 65, yCorner + 65, 20, 20);
			
				break;
			//rolls 4: dot in all four corners
			case 4:
				/* 1.3
				   ...
				   2.4
				*/
				grfx.fillOval(xCorner + 15, yCorner + 15, 20, 20);
				grfx.fillOval(xCorner + 15, yCorner + 65, 20, 20);
				grfx.fillOval(xCorner + 65, yCorner + 15, 20, 20);
				grfx.fillOval(xCorner + 65, yCorner + 65, 20, 20);
			
				break;
			//rolls 5: dot in all four corners along with one in the middle
			case 5:
				/* 1.4
				   .3.
				   2.5
				*/
				grfx.fillOval(xCorner + 15, yCorner + 15, 20, 20);
				grfx.fillOval(xCorner + 15, yCorner + 65, 20, 20);
				grfx.fillOval(xCorner + 40, yCorner + 40, 20, 20);
				grfx.fillOval(xCorner + 65, yCorner + 15, 20, 20);
				grfx.fillOval(xCorner + 65, yCorner + 65, 20, 20);
			
				break;
			//rolls 6: dot in all four corners along with a dot in between the top two and one in between the bottom two
			case 6:
				/* 135
				   ...
				   246
				*/
				grfx.fillOval(xCorner + 15, yCorner + 15, 20, 20);
				grfx.fillOval(xCorner + 15, yCorner + 65, 20, 20);
				grfx.fillOval(xCorner + 40, yCorner + 15, 20, 20);
				grfx.fillOval(xCorner + 40, yCorner + 65, 20, 20);
				grfx.fillOval(xCorner + 65, yCorner + 15, 20, 20);
				grfx.fillOval(xCorner + 65, yCorner + 65, 20, 20);
			
				break;
		}//end switch
	}//end static member drawDice
	
}//end class GameInfo

/**
 * MenuWindow class displays a menu showing statistics about the game in progress
 * eg. wins, losses, money earned, money lost
 *
 * @author Charles Lei
 */
class MenuWindow extends JFrame implements ActionListener
{
	/**********			*
	 * instance variables
	 **********			*/
	 
	/**********
	 * dictionary:
	 *	GameInfo game: stores an object containing all information necessary to run, save, and reload the current game
	 *	JPanel everything: background panel containing all components
	 *	JLabel infoDisplay:
	 *		label containing a description of the current game
	 *		public because the game object changes the displayed text to match the game details
	 *	JPanel infoPanel: panel which contains the label which contains a description of the game, for organization
	 *	JPanel buttonPanel: panel holding all buttons
	 *	JLabel enterNumberPrompt: label prompts the user the enter a number of a new game is wanted
	 *	JTextField enterNumberText: if the user starts a new game, this amount of money is used for both players
	 *	JButton[] menuButtons:
	 *		array of all buttons used in the menu
	 *		public because the first button could either be used to begin a new round or resume an existing one
	 *		the game variable detects this and sets it appropriately
	 **********/
	 
	private GameInfo game;
	
	private JPanel everything = new JPanel();
	
	public JLabel infoDisplay = new JLabel("");
	private JPanel infoPanel = new JPanel();
	
	private JPanel buttonPanel = new JPanel();
	
	private JLabel enterNumberPrompt = new JLabel("New initial money value:");
	private JTextField enterNumberText = new JTextField(10);
	
	public JButton[] menuButtons = 
	 {
		//starts new game
		new JButton("reset money"),
		//either continues current round or starts a new round
		new JButton(""),
		//saves
		new JButton("save current game"),
		//loads
		new JButton("load saved game"),
		//quits
		new JButton("quit")
	 };

	/**********			*
	 * constructors
	 **********			*/
	 
	/**
	 * creates a JFrame with the features of the menu: buttons to start, create, continue, load, save, and quit games
	 * requires a GameInfo object, which it stores (contains all important info for the game)
	 * this is the formal entrypoint, meaning that all actions start from here when the program is initially opened
	 * @param GameInfo game - object containing all information to play the game
	 */
	public MenuWindow(GameInfo game)
	{
		//set the title
		super("Game Menu");
		
		//save the object containing the details of the current stored game
		this.game = game;
		
		//use the game object to initialize the buttons and label to reflect the details of the game
		game.initializeMenu(this);
		
		//set the preferred size of the main label to take up 3/4 of the screen vertically, the whole thing horizontally
		infoDisplay.setPreferredSize(new Dimension(550, 320));
		
		//add the main label to its panel for organizational purposes
		infoPanel.setPreferredSize(new Dimension(600, 320));
		infoPanel.add(infoDisplay);
		
		//this panel takes up the remaining 1/4 of the vertical screen, has a flow layout
		buttonPanel.setPreferredSize(new Dimension(600, 80));
		buttonPanel.setLayout(new FlowLayout());
		
		//buttonPanel contains a label to prompt the user
		enterNumberPrompt.setPreferredSize(new Dimension(150, 30));
		buttonPanel.add(enterNumberPrompt);
		
		//buttonPanel contains an input box to read a number
		buttonPanel.add(enterNumberText);
		
		//buttonPanel also contains all the buttons
		for (JButton button : menuButtons)
		{
			//set the size, add it to the panel, add an action listener
			button.setPreferredSize(new Dimension(145, 30));
			buttonPanel.add(button);
			button.addActionListener(this);
		}//end for
		
		//to the background JPanel, add the main label and the panel containing all other components
		everything.add(infoPanel);
		everything.add(buttonPanel);
		
		//set its size, and give it a box layout (along the y-axis)
		everything.setPreferredSize(new Dimension(600, 400));
		everything.setLayout(new BoxLayout(everything, BoxLayout.Y_AXIS));
		
		//finish setting up the JFrame
		this.add(everything);
		
		this.pack();
		this.setVisible(true);
		this.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
	}//end constructor (GameInfo)
	
	/**********			*
	 * instance methods
	 **********			*/
	
	/**
	 * MenuWindow implements ActionListener, which it uses for buttons stored as instance variables in this class
	 * takes an appropriate action after detecting which button triggered this action
	 * @param ActionEvent ev - event object which is used to find which button was clicked
	 * @return void
	 * @override
	 */
	public void actionPerformed(ActionEvent ev)
	{
		//stores the index of which button (in the contained array of JButtons) was clicked
		int clicked = -1;
		
		//find the index, check every one
		for (int index = 0; index < 5; index++)
		{
			//if found, set the clicked variable
			if (ev.getSource() == menuButtons[index])
			{
				clicked = index;
			}//end if
		}//end for
		
		//react differently depending on which button was clicked
		switch (clicked)
		{
			//user clicked 'start new game' button
			case 0:
				//try to read a number from the enterNumberText variable (textbox)
				boolean success = true;
				try
				{
					Integer.parseInt(enterNumberText.getText());
				}
				catch (NumberFormatException ex)
				{
					success = false;
				}//end try/catch
				
				//if a number was successfully read and parsed, start an entirely new game with that initial money value for players
				if (success)
				{
					int newGameValue = Integer.parseInt(enterNumberText.getText());
					
					//however, the number entered for initial money must be at least 1
					if (newGameValue <= 0)
					{
						//add a prompt to tell the user to enter a valid initial money value
						enterNumberPrompt.setText("<html>New initial money value:<br>(must be at least 1)</html>");
					}
					else
					{
						//starts both user and computer off with amount entered, creates a new menu window with the new game
						new MenuWindow(new GameInfo(newGameValue));
						
						//note: the current window will not be closed after the button is clicked
					}//end if
				}
				else
				{
					//error prompt
					enterNumberPrompt.setText("<html>New initial money value:<br>(valid integer needed)</html>");
				}//end if
				
				break;
			//user clicked 'play round' button
			case 1:
				//close this window
				this.dispose();
				
				//detect if the game has a saved, in progress round (where neither player nor computer reached the goal)
				if (menuButtons[1].getText().equals("play round"))
				{
					//if not, open the window to start a new round
					new StartWindow(game);
				}
				else
				{
					//if so, resume the round by going directly to the game window
					new PigGame(game);
				}//end if
				
				break;
			//user clicked 'save current game' button
			case 2:
				//try to get a file choice from the user
				try
				{
					//display the file chooser
					JFileChooser userChoice = new JFileChooser();
					userChoice.setDialogTitle("select a file to load");
					
					//get the user's choice
					int selected = userChoice.showSaveDialog(this);
					
					if (selected == JFileChooser.APPROVE_OPTION)
					{
						//create the objects which save the game
						FileOutputStream saveTo = new FileOutputStream(userChoice.getSelectedFile());
						ObjectOutputStream saving = new ObjectOutputStream(saveTo);
						
						//saving the game object is all that is necessary; flush and close
						saving.writeObject(game);
						saving.flush();
						saving.close();
					}//end if
				}
				catch (IOException ex)
				{
					//error message
					System.out.println("could not save file: " + ex);
				}//end try/catch
				
				break;
			//user clicked 'load saved game' button
			case 3:
				//load file, print an error message if an exception arises
				try
				{
					//display the file chooser
					JFileChooser userChoice = new JFileChooser();
					userChoice.setDialogTitle("select a file to load");
					
					//get user's choice
					int selected = userChoice.showOpenDialog(this);
					
					if (selected == JFileChooser.APPROVE_OPTION)
					{
						//open the file selected by the user and create an ObjectInputStream
						FileInputStream readFrom = new FileInputStream(userChoice.getSelectedFile());
						ObjectInputStream reading = new ObjectInputStream(readFrom);
						
						//load the data, cast it, close the reader
						GameInfo loadedData = (GameInfo)(reading.readObject());
						reading.close();
						
						//only if the user confirmed a file selection, close this window and start a new one with loaded game info
						new MenuWindow(loadedData);
						this.dispose();
					}//end if
				}
				catch (Exception ex)
				{
					//error prompt
					System.out.println("failed to load file: " + ex);
				}//end try/catch
				
				break;
			//user clicked 'quit' button
			case 4:
				//close the window, don't do anything else
				this.dispose();
				
				break;
		}//end switch
	}//end member actionPerformed
}//end class MenuWindow

/**
 * StartWindow class (contains a textbox for the user to enter a number of at least six)
 * the class which starts the window which sets values for the gamble and point goal
 * also implements an ActionListener, to handle events for its button
 * 
 * @author Charles Lei
 */
class StartWindow extends JFrame implements ActionListener
{
	/**********			*
	 * instance variables
	 **********			*/
	 
	/**********
	 * dictionary:
	 *	GameInfo game: all info for the current game stored in this object
	 *	JPanel everything: background JPanel which contains all components
	 *	JLabel message: label instructing the user
	 *	JPanel messagePanel: panel containing the label for the message; used for organization
	 *	JTextField goalTextbox: textbox to read goal value
	 *	JLabel goalLabel: associated label to identify the goal textbox
	 *	JPanel goal: associated panel to contain the label and textbox
	 *	JTextField gambleTextbox: textbox to contain gamble for the entire game
	 *	JLabel gambleLabel: associated label to instruct the user on entering the gamble value
	 *	JPanel gamble: associated panel for gamble textbox and label
	 *	JButton startGame: checks if values are valid, starts game if acceptable
	 *	JPanel buttonPanel: panel used for the button; organizational
	 **********/
	 
	private GameInfo game;
	
	private JPanel everything = new JPanel();
	
	private JLabel message = new JLabel("Enter a goal value for both players, at least six");
	private JPanel messagePanel = new JPanel();
	
	private JTextField goalTextbox = new JTextField(10);
	private JLabel goalLabel = new JLabel("  enter the goal value");
	private JPanel goal = new JPanel();
	
	private JTextField gambleTextbox = new JTextField(10);
	private JLabel gambleLabel = new JLabel("  enter your gamble ($$)");
	private JPanel gamble = new JPanel();
	
	private JButton startGame = new JButton("start game");
	private JPanel buttonPanel = new JPanel();
	
	/**********			*
	 * constructors
	 **********			*/
	 
	/**
	 * creates a new JFrame which contains fields for the user to enter how much money to gamble, and what the point goal is
	 * and then begins a new game
	 * @param GameInfo game - object which contains data for the user's money, points, etc.
	 */
	public StartWindow(GameInfo game)
	{
		//set title
		super("select a point goal before playing");
		
		//store the information for the current game
		this.game = game;
		
		//set preferred size for one of the labels
		message.setPreferredSize(new Dimension(550, 100));
		message.setFont(new Font("Trebuchet MS", Font.PLAIN, 25));
		//add it to its own panel, and set size for that too
		messagePanel.add(message);
		messagePanel.setPreferredSize(new Dimension(600, 100));
		messagePanel.setLayout(new FlowLayout());
		
		//add a label and textbox to a panel which handles the user's input of the goal for this round
		goalLabel.setPreferredSize(new Dimension(600, 30));
		goalLabel.setFont(new Font("Trebuchet MS", Font.PLAIN, 25));
		goal.add(goalLabel);
		goal.add(goalTextbox);
		//give it a flow layout
		goal.setLayout(new FlowLayout());
		goal.setPreferredSize(new Dimension(600, 100));
		
		//add a label and textbox to a panel which handles the user's input of the gamble for this round
		gambleLabel.setPreferredSize(new Dimension(600, 30));
		gambleLabel.setFont(new Font("Trebuchet MS", Font.PLAIN, 25));
		gamble.add(gambleLabel);
		gamble.add(gambleTextbox);
		
		//give it a flow layout
		gamble.setLayout(new FlowLayout());
		gamble.setPreferredSize(new Dimension(600, 100));
		
		//set size of button to start the game and add an action listener
		startGame.setPreferredSize(new Dimension(400, 80));
		startGame.addActionListener(this);
		//big font
		startGame.setFont(new Font("Trebuchet MS", Font.BOLD, 40));
		
		//add it to its own panel, and set size for that too
		buttonPanel.add(startGame);
		buttonPanel.setPreferredSize(new Dimension(600, 100));
		buttonPanel.setLayout(new FlowLayout());
		
		//add everything to the 'everything' background JPanel
		everything.add(messagePanel);
		everything.add(goal);
		everything.add(gamble);
		everything.add(buttonPanel);
		
		//set the layout of the background JPanel, make it 600 by 400
		everything.setLayout(new BoxLayout(everything, BoxLayout.Y_AXIS));
		everything.setPreferredSize(new Dimension(600, 400));
		
		//finish setting up the JFrame
		this.add(everything);
		this.pack();
		this.setVisible(true);
		this.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
	}//end constructor (GameInfo)
	
	/**********			*
	 * instance methods
	 **********			*/
	 
	/**
	 * this class has an ActionListener which is used to handle events for one button
	 * when the button is clicked, an appropriate response will be generated based on whether the user's input was valid or not
	 * if inputs are considered acceptable, a new game will be initiated (a new window, where the user plays the game)
	 * @param ActionEvent ev - ActionEvent object, unused because there is only one button which uses this class as an ActionListener
	 * @return void
	 * @override
	 */
	public void actionPerformed(ActionEvent ev)
	{
		//indicates if the input in the textboxes were successfully parsed into an integer form
		boolean success = true;
		
		//try to parse the strings entered in the textboxes
		try
		{
			Integer.parseInt(goalTextbox.getText());
			Integer.parseInt(gambleTextbox.getText());
		}
		catch (NumberFormatException ex)
		{
			//in the event of failure, set success to false
			success = false;
		}//end try/catch
		
		//in the event of failure to parse to integer, this IF statement will not be executed
		if (success)
		{
			//store the parsed integers for goal and gamble
			int userInput = Integer.parseInt(goalTextbox.getText());
			int userGamble = Integer.parseInt(gambleTextbox.getText());
			
			//if the goal input was under six, tell the user to try again
			//if the gamble input was under one, tell the user to try again
			//otherwise, start the main game window
			if (userInput < 6 || userGamble < 0)
			{
				//stores an error message to display
				String errorMessage = "<html>Try again. ";
				
				//tell the user that goal was too low
				if (userInput < 6)
				{
					errorMessage += "<br>The goal must be at least six. ";
				}//end if
				
				//tell the user that gamble was too low
				if (userGamble < 0)
				{
					errorMessage += "<br>You cannot gamble a negative amount. ";
				}//end if
				
				//set the text to the JLabel
				message.setText(errorMessage + "</html>");
			}
			else
			{
				//close the current window
				this.dispose();
				
				//set the gamble and the goal value, initialize the game
				game.startGame(userGamble, userInput);
				
				//start the actual game window by passing the GameInfo object
				new PigGame(game);
			}//end if
		}
		else
		{
			//display a different message in case the user enters something unparseable
			message.setText("Enter valid integer values in both fields.");
		}//end if
	}//end member actionPerformed
	
}//end class StartWindow

/**
 * PigGame class
 * sets up the main window (JFrame)
 * and facilitates the actions for the interactive user interface
 * interacts with the GameInfo class by calling its methods and updating the stored states of buttons
 *
 * @author Charles Lei
 */
class PigGame extends JFrame implements ActionListener
{
	/**********			*
	 * instance variables
	 **********			*/
	 
	/**********
	 * dictionary:
	 *	GameInfo game: all relevant data for the game is stored here
	 *	boolean isPlayerTurn:
	 *		boolean representing: true -> player's turn; false -> computer's turn
	 *		public because, upon initialization, this will be set by the game variable to restore saved games
	 *	JPanel everything: background JPanel for graphics, buttons to be put on
	 *	PigGraphics screen: all graphics drawn here
	 *	JPanel buttonPanel: panel for buttons
	 *	JButton[] buttonControls:
	 *		array of all buttons used to control the game
	 *		public because, upon initialization, these buttons will be enabled/disabled as the saved game remembers
	 **********/
	
	private GameInfo game;
	
	public boolean isPlayerTurn = true;
	 
	private JPanel everything = new JPanel();
	
	private PigGraphics screen;
	
	private JPanel buttonPanel = new JPanel();
	
	public JButton[] buttonControls =
	 {
		 //rolls dice for whoever has the current turn
		 new JButton("next roll"),
		 //stops the player's turn
		 new JButton("stop rolling"),
		 //confirms a turn switch
		 new JButton("switch player"),
		 //saves
		 new JButton("save game"),
		 //quits
		 new JButton("exit game")
	 };
	 
	/**********			*
	 * constructors
	 **********			*/
	 
	/**
	 * creates a new PigGame object using a GameInfo object
	 * calls an initialize method from the GameInfo object
	 * where a previously saved game is restored or a new game is set up
	 * @param GameInfo game - the object containing information for the game
	 */
	public PigGame(GameInfo game)
	{
		//create an underlying JFrame as this object, with the specified title
		super("Welcome to the Pig Game oink oink");
		
		//store the game data
		this.game = game;
		
		//tell the game object to restore this window to a previously saved state, if necessary
		game.initializeGameWindow(this);
		
		//create the graphical display, set its size to take up 3/4 of the screen vertically
		screen = new PigGraphics(game);
		screen.setPreferredSize(new Dimension(600, 300));
		
		//make the panel containing the buttons take up the remaining 1/4, and set it to have a flow layout
		buttonPanel.setLayout(new FlowLayout());
		buttonPanel.setPreferredSize(new Dimension(600, 100));
		
		//for all three buttons, add it to the JPanel containing buttons,
		//and also set its action listener, and set the preferred size
		for (JButton button : buttonControls)
		{
			buttonPanel.add(button);
			button.addActionListener(this);
			button.setPreferredSize(new Dimension(150, 40));
		}//end for
		
		//add the graphical display and the buttons to the background panel
		everything.add(screen);
		everything.add(buttonPanel);
		
		//set the background panel's preferred size and layout
		everything.setPreferredSize(new Dimension(600, 400));
		everything.setLayout(new BoxLayout(everything, BoxLayout.Y_AXIS));
		
		//add the 'everything' panel which contains everything
		this.add(everything);
		
		//finish setting up the JFrame
		this.setVisible(true);
		this.pack();
		this.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
	}//end constructor (GameInfo)
	
	/**********			*
	 * instance methods
	 **********			*/
	 
	/**
	 * GameInfo has an ActionListener, used to react to its buttons (stored as instance variables)
	 * when the user clicks these, it will interact with the game (GameInfo object) to update relevant game characteristics
	 * clicking 'next roll' triggers game.nextRoll(), 'stop rolling' disables buttons, 'switch turns' triggers game.endTurn()
	 * clicking 'save game' writes the GameInfo object to a file (it is Serializable), 'quit' triggers a game over window
	 * @param ActionEvent ev - event which is used to find the which button has been clicked
	 * @return void
	 * @override
	 */
	public void actionPerformed(ActionEvent ev)
	{
		//stores the index of the button which the user clicked
		int clicked = -1;
		
		//check every index to find the button which was clicked
		for (int index = 0; index < 5; index++)
		{
			//store the index of the found JButton which activated the event
			if (ev.getSource() == buttonControls[index])
			{
				clicked = index;
			}//end if
		}//end for
		
		//check the index of the button found, match it with a case from 0 to 4
		switch (clicked)
		{
			//user clicked 'next roll'
			case 0:
				//game rolls twice for current player
				//and indicates whether a one has been rolled or the computer wants to stop (true in that case)
				boolean stopRolling = game.nextRoll();
				
				//if the game has rolled a one, then change availability of buttons to force a turn switch
				if (stopRolling)
				{
					//set only the button the switch turns to enabled
					//if it was the computer's turn, then this button should be disabled
					buttonControls[0].setEnabled(false);
					buttonControls[1].setEnabled(false);
					buttonControls[2].setEnabled(true);
				}//end if
				
				//note that: when game.roll(isPlayerTurn) was called, in the event of 1('s), 
				//the game object automatically resets points and adds 25 if two ones were rolled
				
				break;
			//user clicked 'stop rolling'
			case 1:
				//enable only the button to switch turns
				buttonControls[0].setEnabled(false);
				buttonControls[1].setEnabled(false);
				buttonControls[2].setEnabled(true);
			
				break;
			//user clicked 'switch turns'
			case 2:
				//tell the game object to update someone's point value and switch turns
				//stores a boolean indicating true if it is now the player's turn, false otherwise
				//update whose turn it is, according to the returned boolean
				boolean isPlayerTurn = game.endTurn();
				
				//if it is the player's turn, then the player should be able to stop rolling, meaning the second button is enabled
				if (isPlayerTurn)
					buttonControls[1].setEnabled(true);
				
				//enable next roll button, disable switch turn button
				buttonControls[0].setEnabled(true);
				buttonControls[2].setEnabled(false);
				
				//if the game detects that someone won, then disable all buttons except the quit button
				if (game.someoneWon())
				{
					//quit button has index 4, so all other buttons are disabled
					buttonControls[0].setEnabled(false);
					buttonControls[1].setEnabled(false);
					buttonControls[2].setEnabled(false);
					buttonControls[3].setEnabled(false);
				}//end if
				
				break;
			//clicked 'save game' button
			case 3:
				//try to save the game to a file, catch a generic IOException
				try
				{
					//open the file chooser
					JFileChooser userChoice = new JFileChooser();
					userChoice.setDialogTitle("select or create a file to save as");
					
					//get the user's choice
					int selected = userChoice.showSaveDialog(this);
					
					//if the user chose to confirm the saving, then save to the file
					if (selected == JFileChooser.APPROVE_OPTION)
					{
						//get the selected file and create an ObjectOutputStream for it
						FileOutputStream saveTo = new FileOutputStream(userChoice.getSelectedFile());
						ObjectOutputStream saving = new ObjectOutputStream(saveTo);
						
						//save the game (GameInfo objects contain all relevant information to restore games); flush and close
						saving.writeObject(game);
						saving.flush();
						saving.close();
					}//end if
				}
				catch (IOException ex)
				{
					//error prompt
					System.out.println("Failed to save. An IOException has occurred: " + ex);
				}//end try/catch
			
				break;
			//clicked 'quit game' button
			case 4:
				//close the current window
				this.dispose();
				
				//go to a different game over window
				new GameOverWindow(game);
			
				break;
		}//end switch
		
		//save the new state of the buttons (the game memorizes whether each button is enabled or disabled)
		//this is performed regardless of which button is pressed, for consistency
		game.saveButtonStates(buttonControls);
	}//end member actionPerformed
	
}//end class PigGame

/**
 * PigGraphics class
 * contains the implementation of all graphical displays
 * as a constantly repainted JPanel inside the PigGame main window
 * 
 * @author Charles Lei
 */
class PigGraphics extends JPanel
{
	/**********			*
	 * instance variables
	 **********			*/
	 
	/**********
	 * dictionary:
	 *	GameInfo Game: stored state of current game 
	 **********/
	
	GameInfo game;
	
	/**********			*
	 * constructors
	 **********			*/
	 
	/**
	 * creates a new drawable interface, stores a GameInfo object for later use
	 * @param GameInfo game - game to be stored
	 */
	public PigGraphics(GameInfo game)
	{
		//do just as the normal JPanel constructor does
		super();
		
		//except also set the stored game variable
		this.game = game;
	}//end constructor (GameInfo)
	
	/**********			*
	 * instance methods
	 **********			*/
	
	/**
	 * clears and buffers the screen, also tells the game object to draw itself (passes it a Graphics object)
	 * @param Graphics grfx - Graphics object with which to draw
	 * @return void
	 * @override
	 */
	public void paintComponent(Graphics grfx)
	{
		//clear the screen in a buffered manner
		super.paintComponent(grfx);
		
		//tell the game to draw itself using the provided Graphics object
		game.drawState(grfx);
		
		//paint the next frame
		this.repaint();
	}//end member paintComponent
	
}//end class PigGraphics

/**
 * displays a window when the game is over with a recap of the events
 * states amount of money gambled, who won, and whether anyone is out of money or not
 *
 * @author Charles Lei
 */
class GameOverWindow extends JFrame implements ActionListener
{
	/**********			*
	 * instance variables
	 **********			*/
	 
	/**********
	 * dictionary:
	 *	GameInfo game: stored state of the current game
	 *	JPanel everything: background JPanel to hold all components in a neat layout
	 *	JPanel message: panel containing a label which contains text recapping the game
	 *	JLabel displayMessage:
	 *		label which has text that recaps the game
	 *		public because the GameInfo object modifies it to produce a recap
	 *	JPanel returnButton: panel which contains button to return to menu
	 *	JButton returnToMenu: when clicked, closes this window and opens the menu without changing the game info
	 **********/
	
	private GameInfo game;
	
	private JPanel everything = new JPanel();
	
	private JPanel message = new JPanel();
	public JLabel displayMessage = new JLabel("");
	
	private JPanel returnButton = new JPanel();
	private JButton returnToMenu = new JButton("return to menu");
	
	/**********			*
	 * constructors
	 **********			*/
	 
	/**
	 * creates a new game over window, sets up the button to return the the menu and displays a summary of the game
	 * this summary is created by passing the new object itself to the GameInfo object, where the summary is written
	 * @param GameInfo game - object containing all relevant game information
	 */
	public GameOverWindow(GameInfo game)
	{
		//set the title
		super("game concluded");
		
		//store the game information
		this.game = game;
		
		//the displayMessage label will be modified to summarize the game details
		game.initializeGameOver(this);
		
		//set size of and add the summary JLabel to a JPanel, displays text to summarize the game
		message.setPreferredSize(new Dimension(600, 300));
		message.add(displayMessage);
		
		//set size of button which returns user to the menu, adds an action listener
		returnToMenu.setPreferredSize(new Dimension(300, 70));
		returnToMenu.addActionListener(this);
		//big font
		returnToMenu.setFont(new Font("Trebuchet MS", Font.BOLD, 20));
		
		//add the button to a JPanel for organization purposes
		returnButton.setPreferredSize(new Dimension(600, 100));
		returnButton.add(returnToMenu);
		
		//add both the message display and the button to the background panel
		everything.add(message);
		everything.add(returnButton);
		
		//set its layout, size
		everything.setLayout(new BoxLayout(everything, BoxLayout.Y_AXIS));
		everything.setSize(new Dimension(600, 400));
		
		//finish setting up the JFrame
		this.add(everything);
		this.pack();
		this.setVisible(true);
	}//end constructor (GameInfo)
	
	/**********			*
	 * instance methods
	 **********			*/
	 
	/**
	 * this class has an ActionListener which is used for its one button
	 * upon receiving a click, this window is closed, and the menu is restarted (with the stored game, so no data lost)
	 * @param ActionEvent ev - unused, as there is only one button
	 * @return void
	 * @override
	 */
	public void actionPerformed(ActionEvent ev)
	{
		//close the current window
		this.dispose();
		
		//back to the menu
		new MenuWindow(this.game);
	}//end member actionPerformed
	
}//end class GameOverWindow