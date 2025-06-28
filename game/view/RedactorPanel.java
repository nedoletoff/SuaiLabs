package view;

import model.Coordinates;
import model.GameComponent;
import model.GameComponents;
import model.Level;
import model.gameObjects.Spring;
import model.gameObjects.*;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.ArrayList;
import java.util.Objects;

public class RedactorPanel extends JPanel implements ActionListener {
    static final Redactor redactor = new Redactor();
    Level level = new Level("Unnamed");
    String levelName = "Unnamed";
    final Window mainListener;
    final JDialog addObjectDialog;
    final JDialog setObjectDialog;
    Integer tempX = 0;
    Integer tempY = 0;
    String tempComponent;
    final MouseListener mouseListener;
    Timer timer;
    boolean showed = true;
    int tempId = -1;

    public RedactorPanel(Window window) {
        super();
        mainListener = window;
        addObjectDialog = redactor.getAddObjectDialog(this, window.frame);
        setObjectDialog = redactor.getSetObjectDialog(this, window.frame);
        RedactorPanel redactorPanel = this;
        JLabel jLabel = new JLabel(redactor.getBack());
        this.add(jLabel);
        window.frame.getContentPane().add(this);
        jLabel.add(redactor.getAddObjectButton());
        jLabel.add(redactor.getBackButton());
        jLabel.add((redactor.getSaveButton()));
        jLabel.add(redactor.getMoveObjectButton());
        jLabel.add(redactor.getLevelName());
        jLabel.add(redactor.getHideRadio());

        redactor.getBackButton().addActionListener(e -> redactorPanel.actionPerformed(new
                ActionEvent(e.getSource(), e.getID(), "Back")));
        redactor.getAddObjectButton().addActionListener(e -> redactorPanel.actionPerformed((new
                ActionEvent(e.getSource(), 15, "Add object"))));
        redactor.getSaveButton().addActionListener(e -> redactorPanel.actionPerformed(new
                ActionEvent(e.getSource(), 20, "Save")));
        redactor.getLevelName().addActionListener(e -> redactorPanel.actionPerformed(new
                ActionEvent(e.getSource(), 100, e.getActionCommand())));
        redactor.getHideRadio().addActionListener(e -> redactorPanel.actionPerformed(new
                ActionEvent(e.getSource(), 50, e.getActionCommand())));
        redactor.getMoveObjectButton().addActionListener(e -> redactorPanel.actionPerformed(new
                ActionEvent(e.getSource(), 150, e.getActionCommand())));

        mouseListener = new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                super.mouseClicked(e);
                Coordinates coordinates = new Coordinates(e.getLocationOnScreen());
                int id = -1;
                if (e.getClickCount() == 2) {
                    try {
                        id = level.getGameObjectId(coordinates);
                    } catch (RuntimeException exception) {
                        System.out.println(exception);
                    }
                    redactorPanel.actionPerformed(new ActionEvent(e.getSource(), 10,
                            "" + id));
                }
            }
        };

        timer = new Timer(10, e -> repaintLevel());
        timer.start();
    }

    public RedactorPanel(Window window, String levelName) {
        this(window);
        this.levelName = levelName;
        level = Level.load(levelName);
        GameObject.ObjectId = level.getGameObjectsNum();
    }

    private void openChoseObject() {
        addObjectDialog.setVisible(true);
    }

    private void hideAddObjectDialog() {
        addObjectDialog.setVisible(false);
    }

    private void openSetObject() {
        setObjectDialog.setVisible(true);
    }

    private void hideSetObject() {
        setObjectDialog.setVisible(false);
    }

    private void addObjectToLevel() {
        String componentName = tempComponent;
        int x = tempX;
        int y = tempY;
        System.out.println(componentName + " " + x + " " + y);
        switch (tempComponent) {
            case ("player") -> level.addGameObject(new Player(GameComponents.getComponent(tempComponent),
                    x, y));
            case ("enemy") -> level.addGameObject(new Enemy(GameComponents.getComponent(tempComponent),
                    x, y));
            case ("coin") -> level.addGameObject(new Coin(GameComponents.getComponent(tempComponent),
                    x, y));
            case ("spike") -> level.addGameObject(new Spike(GameComponents.getComponent(tempComponent),
                    x, y));
            case ("portal") -> level.addGameObject(new Portal(GameComponents.getComponent(tempComponent),
                    x, y));
            case ("spring") -> level.addGameObject(new Spring(GameComponents.getComponent(tempComponent),
                    x, y));
            default -> level.addGameObject(new GameObject(GameComponents.getComponent(tempComponent),
                    x, y));
        }
        paintObject(level.getGameObject(level.getGameObjectId(new Coordinates(x, y))));
        tempX = 0;
        tempY = 0;
        repaintLevel();
    }

    private void setObject() {
        level.getGameObject(tempId).moveTo(tempX, tempY);
        tempId = -1;
        eraseAll();
    }

    public void repaintLevel() {
        ArrayList<GameObject> gameObjects = level.getLevelsObjects();
        for (GameObject gameObject : gameObjects) {
            paintObject(gameObject);
        }
    }

    private void paintObject(GameObject gameObject) {
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
        g.drawImage(redactor.getBack().getImage(), 0, 0,
                Window.WIDTH, Window.HEIGHT, null);
        hideButtons();
        showButtons();
    }

    private void deleteObject() {
        level.removeGameObject(tempId);
        tempId = -1;
        eraseAll();
    }

    private void renameLevel() {
        level.setLevelName(levelName);
    }

    public void hideButtons() {
        redactor.getBackButton().setVisible(false);
        redactor.getMoveObjectButton().setVisible(false);
        redactor.getAddObjectButton().setVisible(false);
        redactor.getLevelName().setVisible(false);
        redactor.getSaveButton().setVisible(false);
    }

    public void showButtons() {
        redactor.getBackButton().setVisible(true);
        redactor.getMoveObjectButton().setVisible(true);
        redactor.getAddObjectButton().setVisible(true);
        redactor.getLevelName().setVisible(true);
        redactor.getSaveButton().setVisible(true);
    }

    public void save() {
        level.fixLevel();
        repaint();
        level.redactorSave();
    }

    @Override
    public void repaint() {
        super.repaint();
        if (level != null)
            repaintLevel();
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        if (Objects.equals(e.getActionCommand(), "Back")) {
            removeAll();
            mainListener.actionPerformed(new ActionEvent(e.getSource(),
                    e.getID(), "Back to main menu"));
            System.out.println(level);
        }

        switch (e.getID()) {
            case (10) -> {
                if (showed)
                    showButtons();
                tempId = Integer.parseInt(e.getActionCommand());
                removeMouseListener(mouseListener);
                if (tempId != -1)
                    openSetObject();
            }
            case (15) -> openChoseObject();
            case (20) -> save();
            case (50) -> {
                if (showed)
                    hideButtons();
                else
                    showButtons();
                showed = !showed;
            }
            case (100) -> {
                levelName = e.getActionCommand();
                renameLevel();
            }
            case (150) -> {
                hideButtons();
                addMouseListener(mouseListener);
            }
            case (200) -> {
                tempComponent = e.getActionCommand();
                hideAddObjectDialog();
                openSetObject();
            }
            case (300) -> {
                hideSetObject();
                if (tempId == -1)
                    addObjectToLevel();
                else
                    setObject();
            }
            case (301) -> {
                hideSetObject();
                if (tempId != -1) {
                    deleteObject();
                }
            }
            case (350) -> tempX = Integer.parseInt(e.getActionCommand());
            case (400) -> tempY = Integer.parseInt(e.getActionCommand());
            default -> {
                System.out.println(e.getID());
                System.out.println(e.getActionCommand());
            }
        }
    }
}

