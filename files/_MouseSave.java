import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.*;
import java.io.*;

public class MouseSave extends JFrame implements MouseListener, MouseMotionListener, ActionListener
{
	static int startX = -1, startY = -1;
	static int endX = -1, endY = -1;
	Help thing;
	JButton[] buttons = 
	 {
		new JButton("line"),
		new JButton("rectangle"),
		new JButton("clear"),
		new JButton("save"),
		new JButton("load")
	 };
	boolean rr;

	public MouseSave()
	{
		JPanel everything = new JPanel();

		everything.addMouseListener(this);
		everything.addMouseMotionListener(this);
		thing = new Help();
		thing.setPreferredSize(new Dimension(600, 350));
		everything.add(thing);

		for (JButton e : buttons)
			e.addActionListener(this);
		JPanel controls = new JPanel();
		for (JButton e : buttons)
			controls.add(e);
		everything.add(controls);

		everything.setLayout(new BoxLayout(everything, BoxLayout.Y_AXIS));
		this.add(everything);
		this.setVisible(true);
		this.pack();
		this.setSize(600, 400);
	}//end default constructor ()

	//useful
	public void mousePressed(MouseEvent e)
	{
		startX = e.getX();
		startY = e.getY();
		endX = startX;
		endY = startY;
		thing.push(new Yes(startX, startY, endX, endY, (rr) ? 0 : 1));
	}//end mouseSomethinged

	public void mouseDragged(MouseEvent e)
	{
		endX = e.getX();
		endY = e.getY();
		thing.pop(new Yes(startX, startY, endX, endY, (rr) ? 0 : 1));
	}//end

	public void actionPerformed(ActionEvent e)
	{
		if (e.getSource() == buttons[3])
			thing.save(this);
		else if (e.getSource() == buttons[4])
			thing.load(this);
		else if (e.getSource() == buttons[2])
			thing.clear();
		else
			rr = (e.getSource() == buttons[1]);
	}//end
   
	//useless
	public void mouseReleased(MouseEvent e){}//end mouseReleased
	public void mouseEntered(MouseEvent e){}//end mouseEntered
	public void mouseExited(MouseEvent e){}//end mouseExited
	public void mouseClicked(MouseEvent e){}//end mouse
	public void mouseMoved(MouseEvent e){}//end

	public static void main(String[] args)
	{
		new MouseSave();
	}//end static member main
}//end class Mouse
class Help extends JPanel
{
	ArrayList<Yes> drawings = new ArrayList<Yes>();

	public void push(Yes yy)
	{
		drawings.add(yy);
	}//end member push
	public void pop(Yes yy)
	{
		drawings.set(drawings.size() - 1, yy);
	}//end member pop
	public void clear()
	{
		drawings.clear();
	}//end member clear
	public void save(JFrame fr)
	{
		try
		{
			JFileChooser chooser = new JFileChooser();
			chooser.setDialogTitle("())()(((()))))()))())())(())");
			int selected = chooser.showSaveDialog(fr);
			if (selected == JFileChooser.APPROVE_OPTION)
			{
				FileOutputStream saveTo = new FileOutputStream(chooser.getSelectedFile());
				ObjectOutputStream saving = new ObjectOutputStream(saveTo);
				saving.writeObject(drawings);
				saving.flush();
				saving.close();
			}//end if
		}
		catch (IOException ex)
		{
			System.out.println("don't mess with the file");
			System.out.println(ex);
		}//end try/catch
	}//end member save
	public void load(JFrame fr)
	{
		try
		{
			JFileChooser chooser = new JFileChooser();
			chooser.setDialogTitle("())()(((()))))()))())())(())");
			int selected = chooser.showSaveDialog(fr);
			if (selected == JFileChooser.APPROVE_OPTION)
			{
				FileInputStream readFrom = new FileInputStream(chooser.getSelectedFile());
				ObjectInputStream reading = new ObjectInputStream(readFrom);
				drawings = (ArrayList)(reading.readObject());
				reading.close();
			}
		}
		catch (ClassNotFoundException ex)
		{
			System.out.println("ha ha");
		}
		catch (IOException ex)
		{
			System.out.println("don't mess with the files");
			System.out.println(ex);
		}//end try/catch
	}
	public void paintComponent(Graphics grfx)
	{
		grfx.setColor(Color.white);
		grfx.fillRect(0, 0, 1000, 1000);
		
		for (Yes e : drawings)
		{
			e.draw(grfx);
		}//end for

		repaint();
	}//end member paintComponent
}//end
class Yes implements Serializable
{
	final static int RECT = 0, LINE = 1;
	int x, y, xx, yy;
	int form;
	public Yes(int x, int y, int xx, int yy, int form)
	{
		this.x = x;
		this.y = y;
		this.xx = xx;
		this.yy = yy;
		this.form = form;
	}//end
	public void draw(Graphics grfx)
	{
		switch (form)
		{
			case 0:
				grfx.setColor(Color.blue);
				grfx.fillPolygon(new int[]{x, xx, xx, x}, new int[]{y, y, yy, yy}, 4);
				break;
			case 1:
				grfx.setColor(Color.red);
				grfx.drawLine(x, y, xx, yy);
				break;
			default:
				System.out.println("what you drawing fool");
		}//end switch
	}//end
	public String toString()
	{
		return String.format("at %d,%d,%d,%d, and is masked as %d", x, y, xx, yy, form);
	}//end
}//end