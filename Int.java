public class Int {
    int num;

    public void increment() {
        num++;
    }
    public void decrement() {
        num--;
    }
    public void add(Int n) {
        num = num + n.num;
    }
    public void substruct(Int n) {
        num = num - n.num;
    }
    @Override
    public String toString() {
        return "" + num;
    }
}



