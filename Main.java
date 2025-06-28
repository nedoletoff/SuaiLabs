public class Main {
    public static void main(String[] args) {
        try {

            Matrix a = new Matrix(2);
            Matrix b = new Matrix(2);
//          System.out.println(a);
//          System.out.println(b);

            Matrix c = a.product(b);

//          System.out.println(c);

            c = a.sum(b);
//          System.out.println(c);

            a.setElement(1, 1, 0);
            System.out.println(a);
            Matrix r = new Matrix(a);

            //for (int i = 0; i < 9; i++) {
            //    r = r.product(a);
            //    System.out.println(r);
            //}
            Matrix s = new Matrix(10);
            for (int i = 0; i < 10; i++)
                s.setElement(i, i, i);
            for (int i = 9; i > 0; i--)
                s.setElement(9-i, i, 9-i);
            System.out.println(s);
            s.sort();
            System.out.println(s);
        }
        catch (Exception exception) {
             System.out.println(exception);
        }
    }
}

