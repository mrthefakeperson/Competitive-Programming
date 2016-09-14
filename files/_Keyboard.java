import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.colorchooser.*;
import java.util.*;

public class Keyboard extends JFrame implements KeyListener, ActionListener
{
	static Help draw;
	int x = 0, y = 0;
	JButton dotChooser, lineChooser, cl;
	JPanel everything;
	Color dot = Color.blue, line = Color.white;
	public Keyboard()
	{
		super("(((((())))()()(((((((())))))())))");
		everything = new JPanel();
		draw = new Help();
		draw.setPreferredSize(new Dimension(600, 400));
		draw.addKeyListener(this);
		draw.setFocusable(true);
		everything.add(draw);

		JPanel change = new JPanel();
		dotChooser = new JButton("choose dot");
		dotChooser.addActionListener(this);
		change.add(dotChooser);
		dotChooser.setFocusable(false);
		lineChooser = new JButton("choose trail");
		lineChooser.addActionListener(this);
		change.add(lineChooser);
		lineChooser.setFocusable(false);
		cl = new JButton("clear");
		cl.addActionListener(this);
		cl.setFocusable(false);
		change.add(cl);
		change.setFocusable(false);
		everything.add(change);

		everything.setLayout(new BoxLayout(everything, BoxLayout.Y_AXIS));
		this.add(everything);
		this.setVisible(true);
		this.pack();
	}//end default constructor ()
	public static void main(String[] args)
	{
		new Keyboard();
	}//end static member main

	public void actionPerformed(ActionEvent ev)
	{
		if (ev.getSource() == dotChooser)
		{
			System.out.println("dd");
			dot = JColorChooser.showDialog(everything, "Pick Dot Colour", dot);
			draw.setDotColor(dot);
			draw.repaint();
		}
		else if (ev.getSource() == lineChooser)
		{
			line = JColorChooser.showDialog(everything, "Pick Dot Colour", line);
			draw.setLineColor(line);
			draw.repaint();
		}
		else
		{
			draw.clear();
		}//end if
	}//end member actionPerformed
	public void keyTyped(KeyEvent ev){}//end
	public void keyReleased(KeyEvent ev){}//end keyWhatever
	public void keyPressed(KeyEvent ev)
	{
		int kk = ev.getKeyCode() - 37;
		System.out.println(kk);
		Point p;
		switch (kk)
		{
			case 0:
				x--; break;
			case 1:
				y--; break;
			case 2:
				x++; break;
			case 3:
				y++; break;
		}//end switch
		p = new Point(x, y);
		draw.add(p);
	}//end member keyReleased
}//end class Keyboard
class Help extends JPanel
{
	int x = 0, y = 0, direction = -1;
	long lastDraw = System.currentTimeMillis();
	ArrayList<Point> allPoints = new ArrayList<>();
	Color move = Color.blue, trail = Color.green;
	public void clear()
	{
		allPoints.clear();
	}//end
	public void add(Point p)
	{
		allPoints.add(p);
		x = p.x;
		y = p.y;
	}//end member set
	public void setDotColor(Color c)
	{
		move = c;
	}//end member ...
	public void setLineColor(Color c)
	{
		trail = c;
	}//end member ...
	
	public void paintComponent(Graphics grfx)
	{
		super.paintComponent(grfx);
		grfx.setColor(trail);
		for (Point e : allPoints)
		{
			grfx.fillOval(e.x, e.y, 15, 15);
		}//end for
		grfx.setColor(move);
		grfx.fillOval(x, y, 15, 15);
		
		repaint();
	}//end member paintComponent
}//end class Help
class Point
{
	int x, y;
	public Point(int x, int y)
	{
		this.x = x;
		this.y = y;
	}//end constructor (int, int)
}//end class Point