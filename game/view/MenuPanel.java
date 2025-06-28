package view;

import javax.swing.*;
import java.awt.event.*;

public class MenuPanel extends JPanel implements ActionListener {
    static MainMenu mainMenu = new MainMenu();
    Window mainListener;

    public MenuPanel(Window window) {
        mainListener = window;
        MenuPanel menuPanel = this;
        JLabel jLabel = new JLabel(mainMenu.getBack());
        this.add(jLabel);
        window.frame.getContentPane().add(this);
        jLabel.add(mainMenu.getMenu());
        jLabel.add(mainMenu.getGameName());
        final int[] selected = new int[1];
        mainMenu.getMenu().addListSelectionListener(e -> selected[0] = ((JList<?>) e.getSource()).
                getSelectedIndex());
        mainMenu.getMenu().addKeyListener(new KeyAdapter() {
            public void keyPressed(KeyEvent e) {
                if (e.getKeyCode() == KeyEvent.VK_ENTER) {
                    menuPanel.actionPerformed(new ActionEvent(e.getSource(),
                            e.getID(), "Enter " + selected[0]));
                }
            }
        });

        mainMenu.getMenu().addMouseListener(new MouseAdapter() {
            public void mouseClicked(MouseEvent e) {
                if (e.getClickCount() == 2) {
                    menuPanel.actionPerformed(new ActionEvent(e.getSource(),
                            e.getID(), "Enter " + selected[0]));
                }
            }
        });
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        switch (e.getActionCommand()) {
            case ("Enter 3") -> {
                System.exit(0);
            }
            case ("Enter 2") -> {
                removeAll();
                mainListener.actionPerformed(new ActionEvent(e.getSource(),
                        e.getID(), "Go to level redactor"));
            }
            case ("Enter 1") -> {
                removeAll();
                mainListener.actionPerformed(new ActionEvent(e.getSource(),
                        e.getID(), "Go to level menu"));
            }
            case ("Enter 0") -> {
                removeAll();
                mainListener.actionPerformed(new ActionEvent(e.getSource(),
                        777, "start"));

            }
        }
    }
}