import java.io.IOException;

public class Main {
    public static void main(String[] args) throws IOException {
        Settings s = new Settings();
        s.put("main", "first", 998392);
        s.put("new", "first", 234);
        s.put("main", "second", 2252525);
        s.put("main" ,"third", 4523325);
        s.put("main", "last", -10352);
        System.out.println(s);
        s.put("main", "last", 20);
        System.out.println(s);
        System.out.println(s.get("main", "second"));
        Settings ns = new Settings(s);
        System.out.println(s.equals(ns));
        s.delete("main", "second");
        System.out.println(s.equals(ns));

        s.saveToTextFile("test.txt");
        System.out.println(s);
        Settings n = new Settings();
        n.loadFromTextFile("test.txt");
        n.saveToBinaryFile("new.set");
        n.loadFromBinaryFile("new.set");
        System.out.println(n);

    }
}
