import java.io.PrintStream;
import java.sql.Time;
import java.util.Random;

public class Main {
    public static void main(String[] args) {
        Generator test = new Generator(15,6,12);

        System.out.println("Usual version");
        long time = System.currentTimeMillis();
        test.usualGenerate();
        System.out.println("Time - " + (time - System.currentTimeMillis()));
        System.out.println(test.getResult());

        test.clearArrays();
        System.out.println("Parallel version");
        time = System.currentTimeMillis();
        test.parallelGenerate();
        System.out.println("Time - " + (time - System.currentTimeMillis()));

        System.out.println(test.getResult());
    }
}
