package model.gameObjects;

import model.GameComponent;
import model.Level;

public class Portal extends GameObject {
    public Portal(GameComponent gameComponent, int horizontalCoordinate,
                  int verticalCoordinate) {
        super(gameComponent, horizontalCoordinate, verticalCoordinate);
        protection = 0;
        hitPoints = 1;
    }

    @Override
    public void die(Level level) {
        super.die(level);
        level.addPoint();
        level.endLevel = true;
    }
}
