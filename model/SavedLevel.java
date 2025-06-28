package model;

import model.gameObjects.GameObject;

import java.io.*;
import java.util.TreeMap;

public class SavedLevel implements Serializable {
    public int bestTime = 9999;
    public int bestPoints = 0;
    public TreeMap<Integer, GameObject> gameObjects;
    public String levelName;

    public SavedLevel(Level level) {
        gameObjects = level.getGameObjects();
        levelName = level.getLevelName();
    }

    public SavedLevel(SavedLevel other) {
        gameObjects = other.gameObjects;
        levelName = other.levelName;
        bestPoints = other.bestPoints;
        bestTime = other.bestTime;
    }

    public static SavedLevel load(String levelName) {
        levelName = "C:\\Users\\nedoletoff\\IdeaProjects\\game\\levels\\" + levelName + ".lvl";
        System.out.println(levelName);
        try (ObjectInputStream ois = new ObjectInputStream(new FileInputStream(levelName))) {
            return (SavedLevel) ois.readObject();
        } catch (IOException | ClassNotFoundException e) {
            throw new RuntimeException(e);
        }
    }
    public void save(String levelName) {
        levelName = "C:\\Users\\nedoletoff\\IdeaProjects\\game\\levels\\" + levelName + ".lvl";
        try(ObjectOutputStream oos = new ObjectOutputStream(new
                FileOutputStream(levelName))) {
            oos.writeObject(this);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public String toString() {
        return "model.SavedLevel{" +
                "bestTime=" + bestTime +
                ", bestPoints=" + bestPoints +
                ", gameObjects=" + gameObjects +
                ", levelName='" + levelName + '\'' +
                '}';
    }
}
