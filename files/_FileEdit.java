import java.util.Scanner;
import java.io.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class FileEdit extends JFrame implements ActionListener
{
	JButton left, right;
	JLabel instructions;
	JTextField input;
	static boolean mode = true;   //true -> is reading; false -> is writing
	static PrintWriter stuffTxt;
	static Scanner inp;
	
	public FileEdit()
	{
		super("YES");
		JPanel everything = new JPanel();
		
		JPanel ins = new JPanel();
		instructions = new JLabel("writing to stuff.txt");
		instructions.setPreferredSize(new Dimension(400, 15));
		ins.add(instructions);
		ins.setLayout(new FlowLayout());
		everything.add(ins);
		
		everything.add(Box.createRigidArea(new Dimension(400, 10)));
		
		input = new JTextField(10);
		everything.add(input);
		
		everything.add(Box.createRigidArea(new Dimension(400, 10)));
		
		JPanel under = new JPanel();
		left = new JButton("save to file");
		right = new JButton("close file");
		left.setPreferredSize(new Dimension(125, 25));
		right.setPreferredSize(new Dimension(125, 25));
		left.addActionListener(this);
		right.addActionListener(this);
		under.add(left);
		under.add(right);
		under.setLayout(new FlowLayout());
		everything.add(under);
		
		everything.setLayout(new BoxLayout(everything, BoxLayout.Y_AXIS));
		this.add(everything);
		this.pack();
		this.setVisible(true);
	}
	public void actionPerformed(ActionEvent ev)
	{
		if (ev.getSource() == left)
		{
			if (mode)
			{
				stuffTxt.println(input.getText());
				input.setText("");
			}
			else
			{
				if (inp.hasNext())
				{
					input.setText(inp.nextLine());
				}
				else
				{
					input.setText("end of file reached");
					inp.close();
					left.setEnabled(false);
				}
			}
		}
		else
		{
			if (mode)
			{
				mode = false;
				left.setEnabled(false);
				input.setEnabled(false);
				stuffTxt.close();
				left.setText("next line");
				right.setText("open");
			}
			else
			{
				right.setEnabled(false);
				left.setEnabled(true);
				File stuff_ = new File("stuff.txt");
				try
				{
					inp = new Scanner(stuff_);
					instructions.setText("reading from stuff.txt");
				}
				catch (IOException ex)
				{
					System.out.println("file somehow went missing");
				}
			}
		}
	}
	public static void main(String[] args)
	{
		try
		{
			FileWriter stuff = new FileWriter("stuff.txt");
			stuffTxt = new PrintWriter(stuff);
			new FileEdit();
		}
		catch (IOException ex)
		{
			System.out.println("failed to find/create the file");
		}
	}
}