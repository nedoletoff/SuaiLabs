package model.gameObjects;

import model.GameComponent;

public class Spike extends GameObject {

    public Spike(GameComponent component, int horizontalCoordinate,
                 int verticalCoordinate) {
        super(component, horizontalCoordinate, verticalCoordinate);
        damage = 100;
        damageCoefficient[UP] = 1;
        damageCoefficient[LEFT] = 1;
        damageCoefficient[RIGHT] = 1;
        protection = 10;
    }
}
