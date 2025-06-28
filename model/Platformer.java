package model;

import model.gameObjects.GameObject;
import model.gameObjects.Player;

import java.util.TreeSet;

public class Platformer {
    Player player;
    public Level currentLevel;
    public TreeSet<Integer> pressedKeys;

    public Platformer(Player player, Level currentLevel) {
        this.player = player;
        this.currentLevel = currentLevel;
        this.pressedKeys = currentLevel.pressedKeys;
        currentLevel.generateSurface();
    }

    public void update(int timer) {
        if (!currentLevel.endLevel) {
            for (GameObject gameObject : currentLevel.getLevelsObjects())
                gameObject.update(currentLevel);
            currentLevel.setTimer(timer);
        }
    }

}
