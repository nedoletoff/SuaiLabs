package model.gameObjects;

import model.GameComponent;
import model.Level;

public class Coin extends GameObject{

    public Coin(GameComponent component, int horizontalCoordinate, int verticalCoordinate) {
        super(component, horizontalCoordinate, verticalCoordinate);
        hitPoints = 1;
        protection = 0;
    }

    @Override
    public void die(Level level) {
        super.die(level);
        level.addPoint();
    }
}
