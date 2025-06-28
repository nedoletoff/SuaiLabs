public class Main {
    public static void main(String[] args) {
        Complex a = new Complex(2.0, -3.0);
        Complex b = new Complex(-1, -10);

        System.out.println(a);
        System.out.println(b);
        b.add(a);
        System.out.println(b);
        a.multiplication(b);
        System.out.println(a);
    }
}

