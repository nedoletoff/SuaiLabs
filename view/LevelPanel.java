package view;

import javax.swing.*;
import java.awt.event.*;
import java.util.Objects;

public class LevelPanel extends JPanel implements ActionListener {
    protected static LevelMenu menu = new LevelMenu();
    Window mainListener;
    protected JLabel jLabel = new JLabel(menu.getBack());

    public LevelPanel(Window window) {
        mainListener = window;
        LevelPanel levelPanel = this;
        this.add(jLabel);
        window.frame.getContentPane().add(this);
        jLabel.add(menu.getMenu());
        jLabel.add(menu.getGameName());
        jLabel.add(menu.getBackButton());

        menu.getBackButton().addActionListener(e -> levelPanel.actionPerformed(new ActionEvent(e.getSource(),
                e.getID(), "Back")));

        menu.getMenu().addKeyListener(new KeyAdapter() {
            public void keyPressed(KeyEvent e) {
                if (e.getKeyCode() == KeyEvent.VK_ENTER) {
                    System.out.println("Pressed " + menu.getMenu().getSelectedValue());
                    levelPanel.actionPerformed(new ActionEvent(e.getSource(), 777,
                            menu.getMenu().getSelectedValue().split(":")[0]));
                }
            }
        });

        menu.getMenu().addMouseListener(new MouseAdapter() {
            public void mouseClicked(MouseEvent e) {
                if (e.getClickCount() == 2) {
                    levelPanel.actionPerformed(new ActionEvent(e.getSource(), 777,
                            menu.getMenu().getSelectedValue().split(":")[0]));

                }
            }
        });
    }
    @Override
    public void actionPerformed(ActionEvent e) {
        if (Objects.equals(e.getActionCommand(), "Back")) {
            removeAll();
            mainListener.actionPerformed(new ActionEvent(e.getSource(),
                    e.getID(), "Back to main menu"));
        }
        switch (e.getID()) {
           case (777) -> {
               removeAll();
               System.out.println(e.getActionCommand());
               mainListener.actionPerformed(new ActionEvent(e.getSource(),
                       e.getID(), e.getActionCommand()));
           }
            case (999) -> mainListener.actionPerformed(new ActionEvent(e.getSource(),
                   e.getID(), "New level"));
            default -> {
                System.out.println(e.getSource());
                System.out.println(e.getID());
                System.out.println(e.getActionCommand());
            }
        }
    }
}
