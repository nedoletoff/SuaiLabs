package view;

import model.GameComponent;
import model.GameComponents;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class Redactor {
    ImageIcon back;
    JButton backButton;
    JButton saveButton;
    JButton addObjectButton;
    JButton moveObjectButton;
    JTextField levelName;
    JRadioButton hideRadio;

    public Redactor() {
        backButton = new JButton("Back");
        backButton.setBounds(10, 10, 180, 80);
        backButton.setFont(Window.buttonFont);
        backButton.setForeground(Window.buttonFontColor);
        backButton.setBackground(Window.buttonBackground);
        backButton.setHorizontalAlignment(JLabel.CENTER);

        addObjectButton = new JButton("Add object");
        addObjectButton.setBounds(50, 100, 210, 50);
        addObjectButton.setFont(Window.miniButtonFont);
        addObjectButton.setForeground(Window.levelFontColor);
        addObjectButton.setBackground(Window.background);
        addObjectButton.setHorizontalAlignment(JLabel.CENTER);

        saveButton = new JButton("Save");
        saveButton.setBounds(50, 150, 210, 50);
        saveButton.setFont(Window.miniButtonFont);
        saveButton.setForeground(Window.levelFontColor);
        saveButton.setBackground(Window.background);
        saveButton.setHorizontalAlignment(JLabel.CENTER);

        moveObjectButton = new JButton("Move object");
        moveObjectButton.setBounds(50, 200, 210, 50);
        moveObjectButton.setFont(Window.miniButtonFont);
        moveObjectButton.setForeground(Window.levelFontColor);
        moveObjectButton.setBackground(Window.background);
        moveObjectButton.setHorizontalAlignment(SwingConstants.CENTER);

        levelName = new JTextField("Unnamed");
        levelName.setBounds(Window.WIDTH/2 - 150, 100, 300, 60);
        levelName.setFont(Window.miniButtonFont);
        levelName.setForeground(Window.nameFontColor);
        levelName.setOpaque(false);
        levelName.setHorizontalAlignment(SwingConstants.CENTER);



        back = new ImageIcon("C:\\Users\\nedoletoff\\IdeaProjects\\game\\images/game_image.jpg");


        hideRadio = new JRadioButton("Hide");
        hideRadio.setBounds(Window.WIDTH - 105, 10, 105, 25);
        hideRadio.setFont(Window.miniButtonFont);
        hideRadio.setForeground(Window.levelFontColor);
        hideRadio.setOpaque(false);
        levelName.setHorizontalAlignment(SwingConstants.LEFT);
    }

    public JDialog getAddObjectDialog(ActionListener actionListener, JFrame frame) {
        final int[] selected = new int[1];
        JDialog res = new JDialog(frame);
        res.setTitle("Add object");
        res.setIconImage(new ImageIcon(
                "C:\\Users\\nedoletoff\\IdeaProjects\\game\\images\\circle.png").getImage());
        res.setBounds(Window.WIDTH/2 - 150, Window.HEIGHT/2 - 150, 300, 300);
        res.setName("Add object");
        res.setBackground(Window.background);
        res.setFont(Window.levelFont);

        DefaultListModel<String> menuList = new DefaultListModel<>();
        for (GameComponent gc : GameComponents.getComponents()) {
            menuList.addElement(gc.getName());
        }
        JList<String> list = new JList<>(menuList);
        list.addListSelectionListener(e -> selected[0] = ((JList<?>) e.getSource()).         getSelectedIndex());
        list.addKeyListener(new KeyAdapter() {
            public void keyPressed(KeyEvent e) {
                if (e.getKeyCode() == KeyEvent.VK_ENTER) {
                    actionListener.actionPerformed(new ActionEvent(e.getSource(),
                            200, GameComponents.getComponents().get(selected[0]).getName()));
                }
            }
        });

        list.addMouseListener(new MouseAdapter() {
            public void mouseClicked(MouseEvent e) {
                if (e.getClickCount() == 2) {
                    actionListener.actionPerformed(new ActionEvent(e.getSource(),
                            200, GameComponents.getComponents().get(selected[0]).getName()));
                }
            }
        });

        res.add(list);
        return  res;
    }

    public JDialog getSetObjectDialog(ActionListener actionListener, JFrame frame) {
        JDialog res = new JDialog(frame);
        res.setTitle("Set object");
        res.setIconImage(new ImageIcon(
                "C:\\Users\\nedoletoff\\IdeaProjects\\game\\images\\circle.png").getImage());
        res.setBounds(Window.WIDTH/2 - 150, Window.HEIGHT/2 - 150, 300, 300);
        res.setName("Set Object");
        res.setBackground(Window.background);
        res.setFont(Window.levelFont);

        JLabel text = new JLabel("Should be multiple of 5");
        text.setFont(Window.dialogFont);

        JPanel panel = new JPanel();
        GridLayout grid = new GridLayout(3, 2);
        panel.setSize(300, 100);
        panel.setLayout(grid);
        panel.add(new JLabel("X coordinate : "));

        JTextField xCoordinate = new JTextField("0");
        xCoordinate.addActionListener(e -> actionListener.actionPerformed(new
                ActionEvent(e.getSource(), 350, e.getActionCommand())));
        panel.add(xCoordinate);

        panel.add(new JLabel("Y coordinate : "));


        JTextField yCoordinate = new JTextField("0");
        yCoordinate.addActionListener(e -> actionListener.actionPerformed(new
                ActionEvent(e.getSource(), 400, e.getActionCommand())));
        panel.add(yCoordinate);

        JButton confirm = new JButton("Confirm");
        confirm.setName("Confirm");
        confirm.addActionListener(e -> actionListener.actionPerformed(new
                ActionEvent(e.getSource(), 300, e.getActionCommand())));
        panel.add(confirm);

        JButton remove = new JButton("Remove");
        remove.setName("Remove");
        remove.addActionListener(e -> actionListener.actionPerformed(new
                ActionEvent(e.getSource(), 301, e.getActionCommand())));
        panel.add(remove);

        res.add(text, BorderLayout.NORTH);
        res.add(panel, BorderLayout.CENTER);
        return  res;
    }

    public JRadioButton getHideRadio() {
        return hideRadio;
    }

    public JButton getMoveObjectButton() {
        return moveObjectButton;
    }

    public JButton getAddObjectButton() {
        return addObjectButton;
    }

    public JButton getSaveButton() {
        return saveButton;
    }

    public JButton getBackButton() {
        return  backButton;
    }

    public ImageIcon getBack() {
        return back;
    }

    public JTextField getLevelName() {
        return levelName;
    }
}
