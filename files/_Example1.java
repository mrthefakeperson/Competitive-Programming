import java.awt.*;
import javax.swing.*;

public class Example1 extends JFrame
{
	private Example1(JButton[] buttons, JLabel[] labels)
	{
		for (JButton button : buttons)
		{
			this.add(button);
		}//end for
		for (JLabel label : labels)
		{
			this.add(label);
		}//end for

		//set the layout to flow
		this.setLayout(new FlowLayout(FlowLayout.RIGHT));
		
		this.setSize(600,400);
		this.setVisible(true);
	}//end constructor Example1(JButton[])
	private static JButton make(JButton item, int x, int y, int w, int h)
	{
		item.setBounds(x, y, w, h);
		return item;
	}//end static member make
	private static JLabel make(JLabel item, int x, int y, int w, int h)
	{
		item.setBounds(x, y, w, h);
		return item;
	}//end static member make
	public static void main(String[] args)
	{
		JButton[] buttons =
		 {
			new JButton("Button #1"),
			new JButton("Button #2")
		 };
		JLabel[] labels =
		 {
			new JLabel("Label #1"),
			new JLabel("Label #2")
		 };

		new Example1(buttons, labels);
	}//end static member main
}//end class Example