import java.awt.*;
import javax.swing.*;
import java.awt.event.*;
    	
class Example3 extends JFrame
{
	public Example3(String title)
	{
		super(title);
		JComponent HH = new HELP();
		HH.setPreferredSize(new Dimension(300, 200));
		this.add(HH);

		this.pack();
		//this.setSize(300, 200);
		this.setVisible(true);
	}
    	public static void main (String[] args)
    	{
		new Example3("yes");
    	}
}
 
class HELP extends JComponent
{
	static void drawCircle(Graphics grfx, int x, int y, int r)
	{
		grfx.fillOval(x - r, y - r, r * 2, r * 2);
	}//end static member drawCircle
    	public HELP()
    	{
           	repaint();
    	}
    	public void paint (Graphics grfx)
    	{
		grfx.setColor(new Color(255, 0, 0));
		drawCircle(grfx, 0, 0, 4);
		grfx.setColor(new Color(0, 0, 255));
		drawCircle(grfx, 150, 200, 4);
		grfx.setColor(new Color(0, 255, 0));
		drawCircle(grfx, 0, 100, 4);
		grfx.setColor(Color.yellow);
		drawCircle(grfx, 225, 150, 4);
    	}
}