package model.tests;

import model.GameComponent;

import java.io.*;

public class TestComponent {
    public static int successCount = 0;
    public static int failCount = 0;
    public static void main(String[] args) throws FileNotFoundException {
        successCount = 0;
        failCount = 0;
        GameComponent g = new GameComponent("model.gameObjects.Enemy",
                "images\\enemy.png",
                100, 100);
        //System.out.println(g);

        try(ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream("g.data"))) {
            oos.writeObject(g);
            System.out.println("Save test:true");
            successCount++;
        } catch (IOException e) {
            failCount++;
            throw new RuntimeException(e);
        }

        try (ObjectInputStream ois = new ObjectInputStream(new FileInputStream("g.data"))) {
            GameComponent gg = (GameComponent)ois.readObject();
            //System.out.println(gg);
            System.out.println("Load test:" + g.equals(gg));
            successCount++;
        } catch (IOException | ClassNotFoundException e) {
            failCount++;
            throw new RuntimeException(e);
        }
    }
}
