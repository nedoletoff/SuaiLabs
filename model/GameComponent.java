package model;

import java.io.*;
import java.util.Objects;

public class GameComponent implements Serializable {
    public static int num;
    int horizontalSize;
    int verticalSize;
    String name;
    String imageName;
    //ImageIcon png;


    public GameComponent(String name, String imageName,
                         int horizontalSize, int verticalSize) {
        num++;
        this.name = name;
        this.imageName = "C:\\Users\\nedoletoff\\IdeaProjects\\game\\images\\" + imageName;
        //this.png = new ImageIcon(imageLocation);
        this.horizontalSize = horizontalSize;
        this.verticalSize = verticalSize;
    }

    public GameComponent(GameComponent other){
        num++;
        this.name = other.name;
        this.imageName = other.imageName;
        //this.png = new ImageIcon(imageLocation);
        this.horizontalSize = other.horizontalSize;
        this.verticalSize = other.verticalSize;
    }

    public GameComponent(String name) {
        name = "C:\\Users\\nedoletoff\\IdeaProjects\\game\\components\\" + name + ".cmp";
        try (ObjectInputStream ois = new ObjectInputStream(new
                FileInputStream(name))) {
            GameComponent g = new GameComponent((GameComponent) ois.readObject());
            this.name = g.name;
            this.imageName = g.imageName;
            this.horizontalSize = g.horizontalSize;
            this.verticalSize = g.verticalSize;
        } catch (IOException | ClassNotFoundException e) {
            throw new RuntimeException(e);
        }
    }

    public void save() {
        String fileName = "C:\\Users\\nedoletoff\\IdeaProjects\\game\\components\\" + name + ".cmp";
        try (ObjectOutputStream oos = new ObjectOutputStream(new
                FileOutputStream(fileName))) {
            oos.writeObject(this);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public int getHorizontalSize() {
        return horizontalSize;
    }

    public int getVerticalSize() {
        return verticalSize;
    }

    public String getName() {
        return name;
    }

    public String getImageName() {
        return imageName;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        GameComponent that = (GameComponent) o;
        return getHorizontalSize() == that.getHorizontalSize() &&
                getVerticalSize() == that.getVerticalSize() &&
                Objects.equals(getName(), that.getName()) &&
                Objects.equals(getImageName(), that.getImageName());
                //Objects.equals(getPng(), that.getPng());
    }

    @Override
    public int hashCode() {
        return Objects.hash(getHorizontalSize(), getVerticalSize(),
                getName(), getImageName());
    }

    @Override
    public String toString() {
        return "model.GameComponent{" +
                "horizontalSize=" + horizontalSize +
                ", verticalSize=" + verticalSize +
                ", name='" + name + '\'' +
                ", imageLocation='" + imageName + '\'' +
                '}';
    }
}


