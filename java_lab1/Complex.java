public class Complex {
    double num;
    double numi;

    public Complex(double num, double numi) {
        this.num = num;
        this.numi = numi;
    }
    public void set_num(double n) {
        num = n;
    }
    public void set_numi(double ni) {
        numi = ni;
    }
    public void add(Complex a) {
        num += a.num;
        numi += a.numi;
    }
    public void multiplication(Complex a) {
        double temp = num * a.num - numi * a.numi;
        numi = num * a.numi + numi * a.num;
        num = temp;
    }
    @Override 
    public String toString() {
        return "" + num + " + " + numi + "i";
    }
}
