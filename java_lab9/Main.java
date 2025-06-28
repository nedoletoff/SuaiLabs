import static java.lang.Thread.sleep;

public class Main {
    public static void main(String[] args) {
        Client Joe = new Client(5005);
        Client Tom = new Client(20000);

        Thread thread1 = new Thread(() -> {
            System.out.println("Joe sending money to Tom...");
            try {
                Joe.transferMoney(Tom, 5);
            }
            catch (InterruptedException exception) {
                System.out.println(exception);
            }
            System.out.println("Tom receive money, Tom balance:" + Tom);
        }, "Thread1");

        Thread thread2 = new Thread(() -> {
            System.out.println("Tom sending money to Joe...");
            try {
                Tom.transferMoney(Joe, 1000);
            }
            catch (InterruptedException exception) {
                System.out.println(exception);
            }
            System.out.println("Joe receive money, Joe balance:" + Joe);
        }, "Thread2");

        thread1.start();
        thread2.start();
    }
}
