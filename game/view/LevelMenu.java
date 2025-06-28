package view;

import model.Levels;
import model.SavedLevel;

import javax.swing.*;

public class LevelMenu {
    JList<String> menu;
    ImageIcon back;
    JLabel gameName;
    JButton backButton;
    JButton newButton;

    public LevelMenu() {
        backButton = new JButton("Back");
        backButton.setBounds(10, 10, 180, 80);
        backButton.setFont(Window.buttonFont);
        backButton.setForeground(Window.buttonFontColor);
        backButton.setBackground(Window.buttonBackground);
        backButton.setOpaque(false);

        newButton = new JButton("New");
        newButton.setBounds(10, 90, 180, 80);
        newButton.setFont(Window.buttonFont);
        newButton.setForeground(Window.buttonFontColor);
        newButton.setBackground(Window.buttonBackground);
        newButton.setOpaque(false);

        Levels levels = new Levels("C:\\Users\\nedoletoff\\IdeaProjects\\game\\levels");
        int index = 0;
        DefaultListModel<String> menuList = new DefaultListModel<>();
        SavedLevel savedLevel;
        for (String level : levels.getLevelsNames()) {
            savedLevel = SavedLevel.load(level);
            level += ":         best time - " + savedLevel.bestTime;
            level += ":best score - " + savedLevel.bestPoints;
            menuList.add(index++, level);
        }
        backButton.setHorizontalAlignment(SwingConstants.LEFT);

        menu = new JList<>(menuList);
        menu.setBounds(Window.WIDTH / 2 - 800,Window. HEIGHT / 2 - 250,
                1600, 400);
        menu.setName("LevelMenu");
        menu.setFont(Window.miniLevelFont);
        menu.setForeground(Window.levelFontColor);
        menu.setBackground(Window.background);
        menu.setOpaque(false);
        DefaultListCellRenderer listCellRenderer = (DefaultListCellRenderer)
                menu.getCellRenderer();
        listCellRenderer.setHorizontalAlignment(JLabel.LEFT);
        listCellRenderer.setOpaque(false);

        gameName = new JLabel("Circle Adventure");
        gameName.setName("gameName");
        gameName.setFont(Window.nameFont);
        gameName.setForeground(Window.nameFontColor);
        gameName.setHorizontalAlignment(JLabel.CENTER);
        gameName.setBounds(Window.WIDTH / 2 - 400,Window.HEIGHT / 2 - 450,
                800, 200);

        back = new ImageIcon("C:\\Users\\nedoletoff\\IdeaProjects\\game\\images/game_image.jpg");
    }
    public JButton getBackButton() {
        return  backButton;
    }
    public JButton getNewButton() {
        return newButton;
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
