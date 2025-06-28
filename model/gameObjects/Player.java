package model.gameObjects;

import model.Coordinates;
import model.GameComponent;
import model.Level;

import java.awt.event.KeyEvent;

public class Player extends GameObject {
    public Player(GameComponent component, int horizontalCoordinate, int verticalCoordinate) {
        super(component, horizontalCoordinate, verticalCoordinate);
        damage = 1;
        damageCoefficient[DOWN] = 7;
        damageCoefficient[UP] = 3;
        damageCoefficient[LEFT] = 1;
        damageCoefficient[RIGHT] = 1;
        canMove = true;
        hitPoints = 4;
        protection = 0;
        canFall = true;
    }

    public void moveLeft(Level level) {
        Coordinates nextPoint = getCoordinates();
        nextPoint.x -= speed;
        try {
            int id = level.getGameObjectId(nextPoint);
            hit(level.getGameObject(id));
            if (isInHitBox(level.getGameObject(id)))
                return;
            move(-speed, 0);
        }
        catch (RuntimeException ignored) {
            move(-speed, 0);
        }
    }

    public void moveRight(Level level) {
        Coordinates nextPoint = getCoordinates();
        nextPoint.x += 100 + speed;
        try {
            int id = level.getGameObjectId(nextPoint);
            hit(level.getGameObject(id));
            if (isInHitBox(level.getGameObject(id))) {
                return;
            }
            move(speed, 0);
        }
        catch (RuntimeException ignored) {
            move(speed, 0);
        }
    }

    public void jump(Level level) {
        if (level.onSurface(this)) {
            jumpSpeed = -15;
            move(0, jumpSpeed);
        }

    }

    @Override
    public void fall(Level level) {
        super.fall(level);
        if (level.onSurface(this)) {
            jumpSpeed = 10;
        }
        if (jumpSpeed < 10)
            jumpSpeed++;
    }

    @Override
    public void update(Level level) {
        if (hitPoints < 0)
            die(level);
        if (level.pressedKeys.contains(KeyEvent.VK_A)) {
            moveLeft(level);
        }
        if (level.pressedKeys.contains(KeyEvent.VK_D)) {
            moveRight(level);
        }
        if (level.pressedKeys.contains(KeyEvent.VK_SPACE)) {
            jump(level);
        }

        for (GameObject gameObject : level.getLevelsObjects()) {
            if (this.equals(gameObject)) continue;
            if (isInHitBox(gameObject)) {
                hit(gameObject);
                moveOut(gameObject);
            }
        }
        for (GameObject gameObject : level.getLevelsObjects()) {
            if (this.equals(gameObject)) continue;
            if (isStandOn(gameObject)) {
                hit(gameObject);
                return;
            }
        }
        fall(level);
    }
    @Override
    public boolean isStandOn(GameObject other) {
        return  (whereIsObject(other) == DOWN && isNearHitBox(other)) ||
                verticalCoordinate == HEIGHT;
    }

    @Override
    public void die(Level level) {
        super.die(level);
        level.gameOver();
    }
}
