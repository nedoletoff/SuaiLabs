package model.gameObjects;

import model.Coordinates;
import model.GameComponent;
import model.Level;

import java.io.Serializable;
import java.util.Arrays;
import java.util.Objects;

public class GameObject implements Serializable {
    public static final int UP = 0;
    public static final  int DOWN = 1;
    public static final int LEFT = 2;
    public static final int RIGHT = 3;
    public static int HEIGHT = 1080;
    public static int WIDTH = 1920;
    final int id;
    final int speed = 5;
    GameComponent component;
    int horizontalCoordinate;
    int verticalCoordinate;
    int damage = 0;
    int hitPoints = 10;
    int[] damageCoefficient = {0, 0, 0, 0}; //up, down, left, right
    boolean canMove = false;
    int protection = 10;
    public static int ObjectId = 0;
    boolean canFall = false;
    protected int jumpSpeed = 10;


    public static void setFrame(int width, int height) {
        WIDTH = width;
        HEIGHT = height;
        Coordinates.setFrame(width, height);
    }
    public GameObject(GameComponent component, int horizontalCoordinate,
                      int verticalCoordinate) {
        this.component = component;
        this.horizontalCoordinate = horizontalCoordinate - horizontalCoordinate % 5;
        this.verticalCoordinate = verticalCoordinate - verticalCoordinate % 5;
        id = ObjectId++;
    }

    public GameObject(GameComponent component, int horizontalCoordinate,
                      int verticalCoordinate, int damage, int hitPoints,
                      int[] coefficients, boolean canMove) throws Error {

        this.component = component;
        this.horizontalCoordinate = horizontalCoordinate - horizontalCoordinate % 5;
        this.verticalCoordinate = verticalCoordinate - verticalCoordinate % 5;
        if (coefficients.length > 4)
            throw new Error("wrong coefficients");
        System.arraycopy(coefficients, 0, this.damageCoefficient,
                0, coefficients.length);
        this.damage = damage;
        this.hitPoints = hitPoints;
        this.canMove = canMove;
        id = ObjectId++;
    }

    public void setHorizontalCoordinate(int horizontalCoordinate) {
        this.horizontalCoordinate = horizontalCoordinate;
    }

    public void setVerticalCoordinate(int verticalCoordinate) {
        this.verticalCoordinate = verticalCoordinate;
    }

    public void setDamageCoefficient(int[] coefficients) throws Error {
        if (coefficients.length > 4)
            throw new Error("wrong coefficients");
        System.arraycopy(coefficients, 0, this.damageCoefficient,
                0, coefficients.length);
    }

    public void setDamage(int damage) {
        this.damage = damage;
    }

    public void setHitPoints(int hitPoints) {
        this.hitPoints = hitPoints;
    }

    public void setProtection(int protection) {
        this.protection = protection;
    }

    public void setCanMove(boolean canMove) {
        this.canMove = canMove;
    }

    public int getDamage() {
        return damage;
    }

    public int getHitPoints() {
        return hitPoints;
    }

    public int[] getDamageCoefficient() {
        return damageCoefficient;
    }

    public int getId() {
        return id;
    }

    public int[] getHitBox() {
        int[] hitBox = new int[4];
        hitBox[LEFT] = horizontalCoordinate;
        hitBox[RIGHT] = horizontalCoordinate + component.getHorizontalSize();
        hitBox[UP] = verticalCoordinate;
        hitBox[DOWN] = verticalCoordinate + component.getVerticalSize();

        return hitBox;
    }

    public Coordinates getCoordinates() {
        return new Coordinates(horizontalCoordinate, verticalCoordinate);
    }

    public GameComponent getComponent() {
        return component;
    }

    public boolean isCanFall() {
        return canFall;
    }

    public Coordinates whereIsCenter() {
        return new Coordinates(horizontalCoordinate + component.getHorizontalSize() / 2,
                verticalCoordinate + component.getVerticalSize() / 2);
    }

    public boolean isInHitBox(Coordinates coordinates) {
        return isInHitBox(coordinates.x, coordinates.y);
    }

    public boolean isInHitBox(int x, int y) {
        int[] hitBox = getHitBox();
        return  (x >= hitBox[LEFT] && y >= hitBox[UP] &&
                x <= hitBox[RIGHT] && y <= hitBox[DOWN]);
    }

    public boolean isInHitBox(GameObject other) {
        Coordinates center = this.whereIsCenter();
        Coordinates otherCenter = other.whereIsCenter();

        boolean xIntersection =  (Math.abs(center.x - otherCenter.x) <
                this.component.getHorizontalSize() / 2 + other.component.getHorizontalSize() / 2);
        boolean yIntersection = (Math.abs(center.y - otherCenter.y) <
                this.component.getVerticalSize() / 2+ other.component.getVerticalSize() / 2);

        return  (xIntersection && yIntersection);
    }

    public boolean isNearHitBox(GameObject other) {
        Coordinates center = this.whereIsCenter();
        Coordinates otherCenter = other.whereIsCenter();

        boolean xIntersection =  (Math.abs(center.x - otherCenter.x) ==
                this.component.getHorizontalSize() / 2 + other.component.getHorizontalSize() /2 );
        boolean yIntersection = (Math.abs(center.y - otherCenter.y) ==
                this.component.getVerticalSize() / 2 + other.component.getVerticalSize() / 2);

        return  (xIntersection && yIntersection);
    }

    public int whereIsObject(GameObject other) {
        Coordinates myCenter = whereIsCenter();
        Coordinates otherCenter = other.whereIsCenter();
        Coordinates delta = myCenter.minus(otherCenter);

        if (delta.x > 0) {
            if (delta.y > 0) {
                if (delta.x > delta.y)
                    return LEFT;
                else
                    return UP;
            } else {
                if (delta.x > -delta.y)
                    return LEFT;
                else
                    return DOWN;
            }
        }
        else {
            if (delta.y > 0) {
                if (-delta.x > delta.y)
                    return RIGHT;
                else
                    return UP;
            } else {
                if (-delta.x > - delta.y)
                    return RIGHT;
                else
                    return DOWN;
            }
        }
    }

    public void hitOther(GameObject other, int side) {
        if (other.protection < damage * damageCoefficient[side] ||
                damage * damageCoefficient[side] < 0) {
            other.hitPoints -= damage * damageCoefficient[side] - other.protection;
        }
    }

    public void hit(GameObject other) {
        if (this.equals(other))
            return;
        System.out.println(this + "hit" + other);
        hitOther(other, whereIsObject(other));
        other.hitOther(this, other.whereIsObject(this));
    }

    public void moveHorizontal(int horizontalDelta) {
        horizontalCoordinate += horizontalDelta;
        if (horizontalCoordinate > WIDTH)
            horizontalCoordinate = WIDTH;
        else if (horizontalCoordinate < 0)
            horizontalCoordinate = 0;
        horizontalCoordinate -= horizontalCoordinate % 5;
    }

    public void moveVertical(int verticalDelta) {
        verticalCoordinate += verticalDelta;
        if (verticalCoordinate > HEIGHT)
            verticalCoordinate = HEIGHT;
        else if (verticalCoordinate < 0)
            verticalCoordinate = 0;
        verticalCoordinate -= verticalCoordinate % 5;
    }

    public void move(int horizontalDelta, int verticalDelta) {
        if (canMove) {
            moveHorizontal(horizontalDelta);
            moveVertical(verticalDelta);
        }
    }

    public void moveTo(int x, int y) {
        if (x < 0)
            x = 0;
        else if (x > WIDTH)
            x = WIDTH;
        horizontalCoordinate = x - x % 5;

        if (y < 0)
            y = 0;
        else if (y > HEIGHT)
            y = HEIGHT;
        verticalCoordinate = y - y % 5;
    }

    public void moveOut(GameObject other) {
        if (this.equals(other))
            return;
        while (isInHitBox(other)) {
            if (whereIsObject(other) == RIGHT)
                moveHorizontal(-5);
            if (whereIsObject(other) == LEFT)
                moveHorizontal(5);
            if (whereIsObject(other)  == UP)
                moveVertical(5);
            if (whereIsObject(other) == DOWN)
                moveVertical(-5);
        }

    }

    public boolean isStandOn(GameObject other) {
        return true;
    }
    public void update(Level level) {
        fall(level);
        if (hitPoints <= 0) {
            die(level);
            level.getGameObjects().remove(id);
        }
    }

    public void die(Level level) {
        System.out.println(this + "dead");
    }

    public void fall(Level level) {
        if (!level.onSurface(this)) {
            move(0, jumpSpeed);
        }
    }

    public boolean equals(GameObject other) {
        return (id == other.id);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        GameObject other = (GameObject) o;
        return id == other.id &&
                horizontalCoordinate == other.horizontalCoordinate &&
                verticalCoordinate == other.verticalCoordinate &&
                getDamage() == other.getDamage() &&
                getHitPoints() == other.getHitPoints() &&
                canMove == other.canMove && protection == other.protection &&
                Arrays.equals(getDamageCoefficient(), other.getDamageCoefficient());
    }

    @Override
    public int hashCode() {
        int result = Objects.hash(id, horizontalCoordinate,
                verticalCoordinate, getDamage(), getHitPoints(),
                canMove, protection);
        result = 31 * result + Arrays.hashCode(getDamageCoefficient());
        return result;
    }

    @Override
    public String toString() {
        return "model.gameObjects.GameObject{" +
                "id=" + id +
                ", component=" + component +
                ", horizontalCoordinate=" + horizontalCoordinate +
                ", verticalCoordinate=" + verticalCoordinate +
                ", damage=" + damage +
                ", hitPoints=" + hitPoints +
                ", damageCoefficient=" + Arrays.toString(damageCoefficient) +
                ", canMove=" + canMove +
                ", protection=" + protection +
                '}';
    }
}
