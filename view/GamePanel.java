package view;

import model.Coordinates;
import model.GameComponent;
import model.Level;
import model.Platformer;
import model.gameObjects.GameObject;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Objects;

public class GamePanel extends JPanel implements ActionListener {

    GameMenu gameMenu = new GameMenu();
    Platformer platformer;
    final Window mainListener;
    Timer timerPlatformer;
    Timer timer;

    int count = 0;
    KeyListener keyListener = new KeyAdapter() {
        @Override
        public void keyPressed(KeyEvent e) {
            super.keyPressed(e);
            platformer.pressedKeys.add(e.getKeyCode());
            if (e.getKeyCode() == KeyEvent.VK_ESCAPE)
                mainListener.actionPerformed(new ActionEvent(e.getSource(),
                        e.getID(), "Back to main menu"));
        }
        @Override
        public void keyReleased(KeyEvent e) {
            super.keyReleased(e);
            platformer.pressedKeys.remove(e.getKeyCode());
        }
    };

    public GamePanel(Window window, String levelName) {
        super();
        GamePanel gamePanel = this;
        timer = new Timer(1000, e -> gameMenu.setTimer(gameMenu.getTimer()+1));
        timerPlatformer = new Timer(40, e -> {
            platformer.update(gameMenu.getTimer());
            repaintLevel();
            gameMenu.setScore(platformer.currentLevel.getPoints());
            if (platformer.currentLevel.endLevel) {
                platformer.currentLevel.save();
                timerPlatformer.stop();
                timer.stop();
                gamePanel.actionPerformed(new ActionEvent(e.getSource(),
                        993, "End game"));
            }
        });

        mainListener = window;
        Level level = Level.load(levelName);
        platformer = new Platformer(level.getPlayer(), level);
        JLabel jLabel = new JLabel(gameMenu.getBack());
        this.add(jLabel);
        window.frame.getContentPane().add(this);
        jLabel.add(gameMenu.getScoreLabel());
        jLabel.add(gameMenu.getTimerLabel());
        jLabel.add(gameMenu.getBackButton());
        jLabel.add(gameMenu.getRestartButton());

        gameMenu.getBackButton().addActionListener(e -> actionPerformed(new
                ActionEvent(e.getSource(), e.getID(), "Back")));
        gameMenu.getRestartButton().addActionListener(e -> actionPerformed((new
                ActionEvent(e.getSource(), 11, "Restart"))));
        timer.start();
        timerPlatformer.start();
        addKeyListener(keyListener);
        grabFocus();
        System.out.println(Arrays.toString(getKeyListeners()));
    }

    public void repaintLevel() {
        if (count++ == 30) {
            eraseAll();
            count = 0;
        }
        ArrayList<GameObject> gameObjects = platformer.currentLevel.getLevelsObjects();
        for (GameObject gameObject : gameObjects) {
            paintObject(gameObject);
        }
    }

    public void paintObject(GameObject gameObject) {
        ImageIcon icon = new ImageIcon(gameObject.getComponent().getImageName());
        JLabel label = new JLabel(icon);
        Coordinates coordinate = gameObject.getCoordinates();
        GameComponent gameComponent = gameObject.getComponent();
        label.setBounds(coordinate.x, coordinate.y, gameComponent.getHorizontalSize(),
                gameComponent.getVerticalSize());
        Graphics g = getGraphics();
        g.drawImage(icon.getImage(), coordinate.x, coordinate.y,
                gameComponent.getHorizontalSize(), gameComponent.getVerticalSize(),
                null);
    }

    private void eraseAll() {
        Graphics g = getGraphics();
        g.drawImage(gameMenu.getBack().getImage(), 0, 0,
                Window.WIDTH, Window.HEIGHT, null);
        hideButtons();
        showButtons();
    }

    public void hideButtons() {
        gameMenu.getBackButton().setVisible(false);
        gameMenu.getRestartButton().setVisible(false);
        gameMenu.getTimerLabel().setVisible(false);
        gameMenu.getScoreLabel().setVisible(false);
    }

    public void showButtons() {
        gameMenu.getBackButton().setVisible(true);
        gameMenu.getRestartButton().setVisible(true);
        gameMenu.getTimerLabel().setVisible(true);
        gameMenu.getScoreLabel().setVisible(true);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        if (Objects.equals(e.getActionCommand(), "Back")) {
            gameMenu.getEndGameDialog(this,
                    mainListener.frame).setVisible(false);
            mainListener.actionPerformed(new ActionEvent(e.getSource(),
                    e.getID(), "Back to main menu"));
        }
        switch (e.getID()) {
            case (11) -> {
                gameMenu.getEndGameDialog(this,
                        mainListener.frame).setVisible(false);
                mainListener.actionPerformed(new ActionEvent(e.getSource(),
                        e.getID(), "Back to main menu"));
                mainListener.actionPerformed(new ActionEvent(e.getSource(),
                        777, platformer.currentLevel.getLevelName()));
            }
            case (993) -> gameMenu.getEndGameDialog(this,
                    mainListener.frame).setVisible(true);
            case (12) -> {
                gameMenu.getEndGameDialog(this,
                        mainListener.frame).setVisible(false);
                mainListener.actionPerformed(new ActionEvent(e.getSource(), e.getID(),
                        "Go to level menu"));
            }
            default -> {
                System.out.println(e.getSource());
                System.out.println(e.getID());
                System.out.println(e.getActionCommand());
            }
        }

    }
}
