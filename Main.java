public class Main {
    public static void main(String[] args) {
            
        Matrix a = new Matrix(3, 4);
        Matrix b = new Matrix(4, 3);
        Matrix c = new Matrix(3, 4);
        Matrix f = new Matrix(3,3);

        a.setElement(1,1,12);
        a.setElement(1,0, 19);
        c.setElement(1,1,20);
        b.setElement(1,1,20);
        
        
        System.out.println(a);
        System.out.println(c);
        Matrix d = a.sum(c);
        System.out.println(d);
        
        System.out.println(a);
        System.out.println(b);
        Matrix e = a.product(b);
        System.out.println(e);

        SquareMatrix aa = new SquareMatrix(3);
        SquareMatrix bb = new SquareMatrix(3);

        System.out.println(aa);
        System.out.println(bb);

        aa = aa.sum(bb);
        System.out.println(aa);


        Matrix m = new MyMatrix(3, 4);
        System.out.println(m);
        m.setElement(1, 1, 20);
        m.setElement(2, 3, 0);
        System.out.println(m);

        Matrix test = c.sum(m);
        System.out.println(test);
         
    }
}
