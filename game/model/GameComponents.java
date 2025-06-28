package model;

import java.io.File;
import java.util.ArrayList;
import java.util.Objects;

public class GameComponents {
    static ArrayList<GameComponent> components = new ArrayList<>();

    public static void load() {
        String path = "C:\\Users\\nedoletoff\\IdeaProjects\\game\\components\\";
        File[] files = new File(path).listFiles();
        ArrayList<String> componentsNames = new ArrayList<>();
        assert files != null;
        for (File file : files) {
            componentsNames.add(file.getName().split("\\.")[0]);
        }
        for (String componentName : componentsNames) {
            components.add(new GameComponent(componentName));
        }
    }

    public static void save() {
        for (GameComponent gameComponent : components) {
            gameComponent.save();
        }
    }

    public static void newComponent(GameComponent component) {
        components.add(component);
    }

    public static GameComponent getComponent(String name) throws Error {
        for (GameComponent gameComponent : components)
            if (Objects.equals(gameComponent.getName(), name)) {
                return gameComponent;
            }
        throw new Error(name + " doesn't exist");
    }

    public static ArrayList<GameComponent> getComponents() {
        return components;
    }
}
