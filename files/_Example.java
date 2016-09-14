import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class Example extends JFrame implements ActionListener
{
	static JButton[] buttons =
	 {
		make(new JButton("+"), 100, 75),
		make(new JButton("-"), 100, 75),
		make(new JButton("*"), 100, 75),
		make(new JButton("/"), 100, 75),
		make(new JButton("%"), 100, 75),
		make(new JButton("^"), 100, 75)
	 };
	static JLabel operation = make(new JLabel(""), 20, 20);
	static JLabel message = make(new JLabel(""), 200, 100);
	static JTextField[] texts =
	 {
		new JTextField(8),
		new JTextField(8)
	 };

	private Example()
	{
		Color[] colourMapping =
		 {
			Color.blue,
			Color.green,
			Color.black,
			Color.red,
			Color.pink,
			Color.cyan
		 };
		for (int e = 0; e < 6; e++)
		{
			buttons[e].addActionListener(this);
			buttons[e].setForeground(colourMapping[e]);
		}//end for

		JPanel interactive = new JPanel();
		interactive.add(texts[0]);
		interactive.add(operation);
		interactive.add(texts[1]);
		interactive.setLayout(new FlowLayout());

		JPanel messagePanel = new JPanel();
		messagePanel.add(message);

		JPanel buttonThings = new JPanel();
		for (JButton e : buttons)
		{
			buttonThings.add(e);
		}//end for
		buttonThings.setLayout(new GridLayout(2, 3, 10, 10));

		JPanel over = new JPanel();
		over.add(interactive);
		over.add(messagePanel);
		over.add(buttonThings);
		over.setLayout(new BoxLayout(over, BoxLayout.Y_AXIS));

		this.add(over);
		this.pack();
		this.setVisible(true);
	}//end constructor Example()

	public void actionPerformed(ActionEvent ev)
	{
		boolean success = true;
		try
		{
			Double.parseDouble(texts[0].getText());
			Double.parseDouble(texts[1].getText());
		}
		catch (NumberFormatException ex)
		{
			success = false;
			message.setText("invalid inputs");
		}//end try / catch
		operation.setText(((JButton)(ev.getSource())).getText());
		if (success)
		{
			double inputA = Double.parseDouble(texts[0].getText()),
			       inputB = Double.parseDouble(texts[1].getText());
			if (ev.getSource() == buttons[0])
			{
				message.setText(inputA + inputB + "");
			}
			else if (ev.getSource() == buttons[1])
			{
				message.setText(inputA - inputB + "");
			}
			else if (ev.getSource() == buttons[2])
			{
				message.setText(inputA * inputB + "");
			}
			else if (ev.getSource() == buttons[3])
			{
				message.setText(inputA / inputB + "");
			}
			else if (ev.getSource() == buttons[4])
			{
				message.setText(inputA % inputB + "");
			}
			else
			{
				message.setText(Math.pow(inputA, inputB) + "");
			}//end if
		}//end if
	}//end member actionPerformed

	private static JButton make(JButton item, int w, int h)
	{
		item.setPreferredSize(new Dimension(w, h));
		return item;
	}//end static member make
	private static JLabel make(JLabel item, int w, int h)
	{
		item.setPreferredSize(new Dimension(w, h));
		return item;
	}//end static member make
	private static JTextField make(JTextField item, int w, int h)
	{
		item.setPreferredSize(new Dimension(w, h));
		return item;
	}//end static member make

	public static void main(String[] args)
	{
		new Example();
	}//end static member main

}//end class Example