package model.gameObjects;

import model.GameComponent;

public class Spring extends GameObject {
    public Spring(GameComponent component, int horizontalCoordinate, int verticalCoordinate) {
        super(component, horizontalCoordinate, verticalCoordinate);
        canFall = false;
    }

}
