import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.*;

class gui10 extends JFrame implements ActionListener, KeyListener
{
    JPanel pnlButtons = new JPanel();
    DrawStuff drawing = new DrawStuff();
    JPanel background = new JPanel();

    JButton buttons[] = new JButton[3];
    String text[] = {"Set Dot Colour", "Set Line Colour", "Clear"};

    Color line = Color.black;
    Color dot = Color.blue;

    ArrayList<Coord> arrList = new ArrayList<Coord>();

    int x ;
    int y ;

    public gui10()
    {
        super("Key Drawing");

        x = this.getWidth() / 2;
        y = this.getHeight() / 2;

        for (int i = 0; i < buttons.length; i++)
        {
            buttons[i] = new JButton(text[i]);
            buttons[i].addActionListener(this);
            pnlButtons.add(buttons[i]);
            buttons[i].setFocusable(false);
        }

        addKeyListener(this);

        background.setLayout(new BoxLayout(background, BoxLayout.Y_AXIS));

        drawing.setPreferredSize(new Dimension(500, 500));
        drawing.setBorder(BorderFactory.createLineBorder(Color.blue));

        background.add(drawing);
        background.add(pnlButtons);

        add(background);

        pack();
        setVisible(true);

        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }

    public void actionPerformed(ActionEvent e)
    {
        if (buttons[0] == e.getSource())
        {
            dot = JColorChooser.showDialog(background, "Pick Dot Colour", dot);
            drawing.repaint();
        } else if (buttons[1] == e.getSource())
        {
            line = JColorChooser.showDialog(background, "Pick Line Colour", line);
            drawing.repaint();
        } else if (buttons[2] == e.getSource())
        {
            arrList.clear();
            drawing.repaint();
        }
    }

    public void keyReleased(KeyEvent e)
    {
    }

    public void keyTyped(KeyEvent e)
    {
    }

    public void keyPressed(KeyEvent e)
    {
        if (e.getKeyCode() == KeyEvent.VK_UP)
        {
            y -= 5;
            drawing.repaint();
            arrList.add(new gui10.Coord(x, y));
        } else if (e.getKeyCode() == KeyEvent.VK_DOWN)
        {
            y += 5;
            drawing.repaint();
            arrList.add(new gui10.Coord(x, y));
        } else if (e.getKeyCode() == KeyEvent.VK_RIGHT)
        {
            x += 5;
            drawing.repaint();
            arrList.add(new gui10.Coord(x, y));
        } else if (e.getKeyCode() == KeyEvent.VK_LEFT)
        {
            x -= 5;
            drawing.repaint();
            arrList.add(new gui10.Coord(x, y));
        }
    }


    class DrawStuff extends JPanel
    {

        public DrawStuff()
        {
            repaint();
        }

        public void paintComponent(Graphics g)
        {
            super.paintComponent(g);

            g.setColor(line);
            for (Coord c : arrList)
            {
                g.fillOval(c.x + getWidth()/2, c.y + getHeight()/2, 10, 10);
            }

            drawing.repaint();

            g.setColor(dot);
            //g.fillOval(this.getWidth()/2, this.getHeight()/2, 10, 10);
            g.fillOval(gui10.this.x + getHeight()/2, gui10.this.y + getWidth()/2, 10, 10);
            //g.fillOval(Coord.x - 5, Coord.y - 5, 10, 10);
        }
    }

    class Coord
    {
        int x;
        int y;

        public Coord(int a, int b)
        {
            x = a;
            y = b;
        }
    }

    public static void main(String[] args)
    {
        new gui10();
    }
}