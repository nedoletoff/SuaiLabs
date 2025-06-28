package model;

import java.awt.*;
import java.util.Objects;

public class Coordinates {
    static int WIDTH = 1080;
    static int HEIGHT = 1080;
    public int x;
    public int y;

    public Coordinates(Point point) {
        x = point.x;
        y = point.y;
    }

    public Coordinates(int x, int y) {
        this.x = x;
        this.y = y;
    }

    public static void setFrame(int width, int height) {
        WIDTH = width;
        HEIGHT = height;
    }

    public void add(int deltaX, int deltaY) {
        if (x + deltaX < WIDTH && x + deltaX > 0)
            x += deltaX;
        else if (deltaX > 0)
            x = WIDTH;
        else
            x = 0;
        if (y + deltaY < HEIGHT && y + deltaY > 0)
            y += deltaY;
        else if (deltaY > 0)
            y = HEIGHT;
        else
            y = 0;
    }

    public Coordinates minus(Coordinates other) {
        return new Coordinates(x - other.x, y - other.y);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Coordinates that = (Coordinates) o;
        return x == that.x && y == that.y;
    }

    @Override
    public int hashCode() {
        return Objects.hash(x, y);
    }

    @Override
    public String toString() {
        return "model.Coordinates{" +
                "x=" + x +
                ", y=" + y +
                '}';
    }
}
