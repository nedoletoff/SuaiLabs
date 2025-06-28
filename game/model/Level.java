package model;

import model.gameObjects.GameObject;
import model.gameObjects.Player;
import model.gameObjects.Portal;
import org.jetbrains.annotations.NotNull;

import java.util.*;

public class Level {
    String levelName;
    int timer = 9999;
    int points = 0;
    TreeMap<Integer, GameObject> gameObjects;
    public TreeSet<Integer> pressedKeys;
    Surface surface = new Surface();
    public boolean endLevel;
    public static class Surface {
        Map<Integer, List<Integer>> surface;

        public Surface() {
            surface = new TreeMap<>();
        }

        public void put(Integer x, Integer y) {
            if (surface.get(x) != null) {
                surface.get(x).add(y);
                Collections.sort(surface.get(x));
            } else {
                surface.put(x, new ArrayList<>());
                surface.get(x).add(y);
            }
        }

        public int get(Integer x, int y) {
            if (surface.get(x) != null) {
                for (int i = 0; i < surface.get(x).size(); i++)
                    if (y <= surface.get(x).get(i))
                        return surface.get(x).get(i);
            }
            return GameObject.HEIGHT;
        }
    }

    public Level(String levelName) {
        this.levelName = levelName;
        this.gameObjects = new TreeMap<>();
        pressedKeys = new TreeSet<>();
    }

    public void addGameObject(@NotNull GameObject gameObject) {
        Integer id = gameObject.getId();
        if (!gameObjects.containsKey(id))
            gameObjects.put(id, gameObject);
    }

    public void removeGameObject(Integer id) {
        gameObjects.remove(id);
    }

    public void setLevelName(String levelName) {
        this.levelName = levelName;
    }

    public String getLevelName() {
        return levelName;
    }

    public int getGameObjectsNum() {
        return gameObjects.size();
    }

    public GameObject getGameObject(Integer id) {
        return gameObjects.get(id);
    }

    public ArrayList<GameObject> getLevelsObjects() {
        Iterator<GameObject> it = gameObjects.values().iterator();
        ArrayList<GameObject> arrayList = new ArrayList<>();
        while (it.hasNext())
            arrayList.add(it.next());
        return arrayList;
    }

    public int getGameObjectId(Coordinates coordinates) throws RuntimeException{
        for (GameObject gc : gameObjects.values()) {
            if (gc.isInHitBox(coordinates))
                return gc.getId();
        }
        throw new RuntimeException("There is no object");
    }

    public TreeMap<Integer, GameObject> getGameObjects() {
        return gameObjects;
    }
    public int getPoints() {
        return points;
    }

    public int getTimer() {
        return timer;
    }

    public void setTimer(int timer) {
        this.timer = timer;
    }

    public void addPoint() {
        points++;
    }

    public static @NotNull Level load(String filename) {
        SavedLevel sl = SavedLevel.load(filename);
        Level l = new Level(sl.levelName);
        l.gameObjects = sl.gameObjects;
        return l;
    }

    public void save() {
        SavedLevel sl = SavedLevel.load(levelName);
        sl.bestPoints = Math.max(sl.bestPoints, getPoints());
        sl.bestTime = Math.min(sl.bestTime, getTimer());
        sl.save(levelName);
    }

    public void redactorSave() {
        SavedLevel sl = new SavedLevel(this);
        sl.save(levelName);
    }

    public void generateSurface() {
        surface = new Surface();
        for (GameObject gc : getLevelsObjects()) {
            for (GameObject gc2 : getLevelsObjects()) {
                if (gc.equals(gc2)) continue;
                if (Objects.equals(gc.getComponent().getName(), "player")) continue;
                if (Objects.equals(gc.getComponent().getName(), "spike")) continue;
                if (Objects.equals(gc.getComponent().getName(), "coin")) continue;
                if (Objects.equals(gc.getComponent().getName(), "portal")) continue;
                if (Objects.equals(gc.getComponent().getName(), "enemy")) continue;
                if (gc.isStandOn(gc2)) {
                    for (int i = gc.getHitBox()[GameObject.LEFT]; i <=
                            gc.getHitBox()[GameObject.RIGHT]; i+=5)
                        surface.put(i, gc.getHitBox()[GameObject.UP]);
                    break;
                }
            }
        }
    }

    public boolean onSurface(@NotNull GameObject gameObject) {
        if (!gameObject.isCanFall())
            return true;
        int down = gameObject.getHitBox()[GameObject.DOWN];
        for (int i = gameObject.getHitBox()[GameObject.LEFT]; i <=
                gameObject.getHitBox()[GameObject.RIGHT]; i+= 5)
            if (surface.get(i, down ) == down)
                return true;
        return false;
    }

    public Player getPlayer() throws RuntimeException {
        for (GameObject gc : getLevelsObjects()) {
            if (Objects.equals(gc.getComponent().getName(), "player")) {
                return (Player) gc;
            }
        }
        throw new RuntimeException("model.gameObjects.Player not found");
    }
    public void fixLevel() {
        boolean playerCheck = false;
        boolean portalCheck = false;

        for (GameObject gc : getLevelsObjects()) {
            if (Objects.equals(gc.getComponent().getName(), "player")) {
                playerCheck = true;
            }
            if (Objects.equals(gc.getComponent().getName(), "portal")) {
                portalCheck = true;
            }
        }
        if (!playerCheck)
            addGameObject(new Player(GameComponents.getComponent("player"),
                    0, 900));
        if (!portalCheck)
            addGameObject(new Portal(GameComponents.getComponent("portal"),
                    100, 900));

        generateSurface();
        for (GameObject gc : getLevelsObjects()) {
            while (!onSurface(gc)) {
                System.out.println("falling " + gc);
                gc.fall(this);
            }
        }
    }

    public void gameOver() {
        timer = 9999;
        points = 0;
        endLevel = true;
    }

    @Override
    public String toString() {
        return "model.Level{" +
                "levelName='" + levelName + '\'' +
                ", timer=" + timer +
                ", points=" + points +
                ", gameObjects=" + gameObjects +
                ", pressedKeys=" + pressedKeys +
                '}';
    }
}

