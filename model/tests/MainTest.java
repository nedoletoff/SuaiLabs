package model.tests;

import java.io.FileNotFoundException;

public class MainTest {
    public static void main(String[] args) throws FileNotFoundException {
        int fail;
        int success;

        System.out.println("\ntest component:");
        TestComponent.main(args);
        fail = TestComponent.failCount;
        success = TestComponent.successCount;
        System.out.println("success: " + success);
        System.out.println("fail: " + fail);

        System.out.println("\ntest game object:");
        TestGameObject.main(args);
        fail = TestGameObject.failCount;
        success = TestGameObject.successCount;
        System.out.println("success: " + success);
        System.out.println("fail: " + fail);

        System.out.println("\ntest player:");
        TestPlayer.main(args);
        fail = TestPlayer.failCount;
        success = TestPlayer.successCount;
        System.out.println("success: " + success);
        System.out.println("fail: " + fail);

        System.out.println("\ntest level:");
        TestLevel.main(args);
        fail = TestLevel.failCount;
        success = TestLevel.successCount;
        System.out.println("success: " + success);
        System.out.println("fail: " + fail);
    }
}
