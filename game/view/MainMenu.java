package view;

import javax.swing.*;

public class MainMenu {
    JList<String> menu;
    ImageIcon back;
    JLabel gameName;

    public MainMenu() {
        DefaultListModel<String> menuList = new DefaultListModel<>();
        menuList.addElement("Start");
        menuList.addElement("Chose Level");
        menuList.addElement("Level Editor");
        menuList.addElement("Exit");

        menu = new JList<>(menuList);
        menu.setBounds(Window.WIDTH / 2 - 200,Window. HEIGHT / 2 - 150,
                400, 400);
        menu.setName("Menu");
        menu.setFont(Window.menuFont);
        menu.setForeground(Window.menuFontColor);
        menu.setBackground(Window.background);
        menu.setOpaque(false);
        DefaultListCellRenderer listCellRenderer = (DefaultListCellRenderer)
                menu.getCellRenderer();
        listCellRenderer.setHorizontalAlignment(JLabel.CENTER);

        gameName = new JLabel("Circle Adventure");
        gameName.setName("gameName");
        gameName.setFont(Window.nameFont);
        gameName.setForeground(Window.nameFontColor);
        gameName.setHorizontalAlignment(JLabel.CENTER);
        gameName.setBounds(Window.WIDTH / 2 - 400,Window.HEIGHT / 2 - 450,
                800, 200);

        back = new ImageIcon("C:\\Users\\nedoletoff\\IdeaProjects\\game\\images/menu_image.jpg");
    }

    public ImageIcon getBack() {
        return back;
    }

    public JLabel getGameName() {
        return gameName;
    }

    public JList<String> getMenu() {
        return menu;
    }
}
