package model.tests;

import model.Coordinates;
import model.GameComponent;
import model.gameObjects.GameObject;

public class TestGameObject {
    public static int successCount = 0;
    public static int failCount = 0;
    public static void main(String[] args) {
        successCount = 0;
        failCount = 0;
        int x = 100;
        int y = 100;
        Coordinates coordinates = new Coordinates(x, y);
        GameComponent component = new GameComponent("circle",
                "images/circle.png", 100, 100);
        GameObject gameObject = new GameObject(component, x, y);
        GameObject gameObject1 = new GameObject(component, x*10, 0);
        GameObject gameObject2 = new GameObject(component, 0, 0);


        System.out.println("getCoordinates test:"
                + coordinates.equals(gameObject.getCoordinates()));
        if (coordinates.equals(gameObject.getCoordinates()))
            successCount++;
        else failCount++;

        System.out.println("getGameComponent test:"
                + component.equals(gameObject.getComponent()));
        if (component.equals(gameObject.getComponent()))
            successCount++;
        else failCount++;

        System.out.println("isInHitBox test1:" +
                gameObject.isInHitBox(gameObject));
        if (gameObject.isInHitBox(gameObject))
            successCount++;
        else failCount++;

        System.out.println("isInHitBox test2:" +
                !gameObject.isInHitBox(gameObject1));
        if (!gameObject.isInHitBox(gameObject1))
            successCount++;
        else failCount++;

        System.out.println("isInHitBox test3:" +
                gameObject.isInHitBox(110, 110));
        if (gameObject.isInHitBox(110, 110))
            successCount++;
        else failCount++;

        System.out.println("isInHitBox test4:" +
                !gameObject.isInHitBox(110, 1000));
        if (!gameObject.isInHitBox(110, 1000))
            successCount++;
        else failCount++;

        System.out.println("isNearHitBox test1:" +
                gameObject.isNearHitBox(gameObject2));
        if (gameObject.isNearHitBox(gameObject2))
            successCount++;
        else failCount++;

        System.out.println("isNearHitBox test2:" +
                gameObject2.isNearHitBox(gameObject));
        if (gameObject2.isNearHitBox(gameObject))
            successCount++;
        else failCount++;

        System.out.println("isNearHitBox test3:" +
                !gameObject.isNearHitBox(gameObject1));
        if (!gameObject.isNearHitBox(gameObject1))
            successCount++;
        else failCount++;

       System.out.println("whereIsObject test1:" +
               (gameObject.whereIsObject(gameObject2) == GameObject.UP));
        if (gameObject.whereIsObject(gameObject2) == GameObject.UP)
            successCount++;
        else failCount++;

        System.out.println("whereIsObject test2:" +
                (gameObject2.whereIsObject(gameObject) == GameObject.DOWN));
        if (gameObject2.whereIsObject(gameObject) == GameObject.DOWN)
            successCount++;
        else failCount++;

        System.out.println("whereIsObject test3:" +
                (gameObject.whereIsObject(gameObject1) == GameObject.RIGHT));
        if (gameObject.whereIsObject(gameObject1) == GameObject.RIGHT)
            successCount++;
        else failCount++;

        System.out.println("whereIsObject test4:" +
                (gameObject1.whereIsObject(gameObject) == GameObject.LEFT));
        if (gameObject1.whereIsObject(gameObject) == GameObject.LEFT)
            successCount++;
        else failCount++;

        System.out.println("isStandOn test1:" +
                gameObject.isStandOn(gameObject2));
        if (gameObject.isStandOn(gameObject2))
            successCount++;
        else failCount++;

        System.out.println("isStandOn test2:" +
                gameObject2.isStandOn(gameObject));
        if (gameObject2.isStandOn(gameObject))
            successCount++;
        else failCount++;
    }
}
