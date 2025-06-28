public class Main {
    public static void main(String[] args) {
        SortedIntegerList l = new SortedIntegerList(true);
        l.add(1);
        l.add(2);
        l.add(3);
        l.add(0);
        l.add(5);
        l.add(5);
        l.add(5);
        l.add(-5);
        System.out.println(l);
        l.remove(3);
        l.remove(11);
        System.out.println(l);

        SortedIntegerList nl = new SortedIntegerList(l);
        System.out.println(l.equals(nl));
        nl.remove(1);
        System.out.println(l.equals(nl));

        SortedIntegerList a = new SortedIntegerList(true);
        /*
        a.add(1);
        a.add(1);
        a.add(2);
        a.add(3);

        a.add(0);
        a.add(5);
        a.add(5);
        a.add(5);
        a.add(-5);
        a.remove(1);
        a.remove(88);
        */
        //a.add(1);
        //System.out.println(a);

        //System.out.println(a.splitList());
        //System.out.println(a);
    }
}

