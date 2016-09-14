import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class Animals extends JFrame implements ActionListener
{
	JButton[] buttons =
	 {
		new JButton("octopus"),
		new JButton("cardinal"),
		new JButton("giraffe"),
		new JButton("butterfly")
	 };
	ImageIcon[] images = new ImageIcon[4];
	public Animals()
	{
		for (int e = 0; e < 4; e++)
		{
			images[e] = new ImageIcon(buttons[e].getText() + ".jpg");
			images[e] = new ImageIcon(images[e].getImage().getScaledInstance(170, 170, Image.SCALE_SMOOTH));
			buttons[e].setIcon(images[e]);
			buttons[e].setPreferredSize(new Dimension(170, 170));
			buttons[e].addActionListener(this);
			this.add(buttons[e]);
		}//end for

		this.setLayout(new GridLayout(2, 2));
		this.pack();
		this.setVisible(true);
	}//end default constructor ()
	public void actionPerformed(ActionEvent ev)
	{
		int e;
		if (ev.getSource() == buttons[0])	e = 0;
		else if (ev.getSource() == buttons[1])	e = 1;
		else if (ev.getSource() == buttons[2])	e = 2;
		else 					e = 3;

		Rectangle qq = this.getBounds();
		if (buttons[e].getIcon() == images[e])
			buttons[e].setIcon(null);
		else
			buttons[e].setIcon(images[e]);
	}//end member actionPerformed
	public static void main(String[] args)
	{
		new Animals();
	}//end static member main
}//end class Animals