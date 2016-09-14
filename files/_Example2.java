import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class Example2 extends JFrame implements ActionListener
{
	static JButton[] buttons =
	 {
		make(new JButton("multiply"), 100, 75),
		make(new JButton("add"), 100, 275)
	 };
	static JLabel[] labels =
	 {
		make(new JLabel("Label A"), 20, 20),
		make(new JLabel("Label B"), 200, 200)
	 };
	static JTextField[] texts =
	 {
		make(new JTextField(8), 200, 100),
		make(new JTextField(8), 200, 100)
	 };
	static boolean _1Enabled = true;

	private Example2()
	{
		JPanel pnIFrame, pnIA, pnIB;

		pnIA = new JPanel();
		pnIA.setLayout(new BoxLayout(pnIA, BoxLayout.Y_AXIS));
		pnIA.setBorder(BorderFactory.createLineBorder(Color.red));
		pnIA.add(labels[0]);
		pnIA.add(Box.createRigidArea(new Dimension(20, 100)));
		texts[0].setText("Text A");
		pnIA.add(texts[0]);

		pnIB = new JPanel();
		pnIB.setLayout(new BoxLayout(pnIB, BoxLayout.X_AXIS));
		pnIB.setBorder(BorderFactory.createLineBorder(Color.blue));
		pnIB.add(labels[1]);
		pnIB.add(Box.createHorizontalGlue());
		texts[1].setText("Text B");
		pnIB.add(texts[1]);

		pnIFrame = new JPanel();
		pnIFrame.setBackground(Color.green);
		pnIFrame.setLayout(new BoxLayout(pnIFrame, BoxLayout.X_AXIS));
		pnIFrame.add(pnIA);
		pnIFrame.add(pnIB);		

		this.add(pnIFrame);
		this.pack();
		this.setVisible(true);
	}//end constructor Example2()

	public void actionPerformed(ActionEvent ev)
	{		

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
		new Example2();
	}//end static member main

}//end class Example