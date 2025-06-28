import java.io.FileNotFoundException;

public class MainTest {
    public static void main(String[] args) throws FileNotFoundException {
        System.out.println("GameComponent:");
        TestComponent.main(args);
        System.out.println("\nResults: success " + TestComponent.successCount +
                "; fail " + TestComponent.failCount + ";\n\n");

        System.out.println("Player:");
        TestPlayer.main(args);
        System.out.println("\nResults: success " + TestPlayer.successCount +
                "; fail " + TestPlayer.failCount + ";\n\n");

        System.out.println("GameObject:");
        TestGameObject.main(args);
        System.out.println("\nResults: success " + TestGameObject.successCount +
                "; fail " + TestGameObject.failCount + ";\n\n");

        System.out.println("Level:");
        TestLevel.main(args);
        System.out.println("\nResults: success " + TestLevel.successCount +
                "; fail " + TestLevel.failCount + ";\n\n");

    }
}
