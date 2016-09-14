import java.awt.*;
import javax.swing.*;
import java.awt.event.*;
    	
class Example3 extends JFrame
{
	public Example3(String title)
	{
		super(title);
		JPanel HH = new Help();
		HH.setPreferredSize(new Dimension(100, 100));
		this.add(HH);

		this.pack();
		this.setVisible(true);
	}//end default constructor
    	public static void main (String[] args)
    	{
		new Example3("OK");
    	}//end static member main
}//end class Example3

class Help extends JPanel
{
	static void drawCircle(Graphics grfx, int x, int y, int r)
	{
		grfx.fillOval(x - r, y - r, r * 2, r * 2);
	}//end static member drawCircle
	static Color[] colours =
	 {
		Color.green,
		Color.yellow,
		Color.orange,
		Color.red
	 };
	public void paintComponent(Graphics grfx)
	{
		super.paintComponent(grfx);
		
		int x = 50, y = 50;
		for (int e = 0; e < 4; e++)
		{
			//add a small border
			grfx.setColor(Color.black);
			drawCircle(grfx, x, y, 50 - 10 * e);
			//draw the coloured ring
			grfx.setColor(colours[e]);
			drawCircle(grfx, x, y, 50 - 10 * e - 1);
		}//end for
	}//end member paintComponent
}//end class Help