import model.GameComponent;
import model.GameComponents;

public class CreateComponents {
    public static void main(String[] args) {
        GameComponent player = new GameComponent("player", "circle.png",
                100, 100);
        GameComponent block = new GameComponent("block", "block2.png",
                100, 100);
        GameComponent enemy = new GameComponent("enemy", "enemy.png",
                100, 100);
        GameComponent coin = new GameComponent("coin", "coin.png",
                50, 50);
        GameComponent spring = new GameComponent("spring", "spring.png",
                50, 80);
        GameComponent spike = new GameComponent("spike", "spike.png",
                100, 100);
        GameComponent portal = new GameComponent("portal", "portal.png",
                100, 150);
        GameComponents.newComponent(player);
        GameComponents.newComponent(block);
        GameComponents.newComponent(enemy);
        GameComponents.newComponent(coin);
        GameComponents.newComponent(spring);
        GameComponents.newComponent(spike);
        GameComponents.newComponent(portal);
        GameComponents.save();

    }
}
