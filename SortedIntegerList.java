import java.util.*;

public class SortedIntegerList {
    final boolean withRepeats;
    LinkedList<Integer> list;

    public SortedIntegerList(boolean withRepeats) {
        this.withRepeats = withRepeats;
        this.list = new LinkedList<Integer>();
    }

    public SortedIntegerList(SortedIntegerList other) {
        this.withRepeats = other.withRepeats;
        this.list = new LinkedList<Integer>(other.list);
    }

    public void add(int value) {
        if (this.withRepeats)
            this.addWithRepeats(value);
        else
            this.addNoRepeats(value);
    }

    public void remove(int value) {
        ListIterator<Integer> it = list.listIterator();
        while (it.hasNext()) {
            if (it.next() == value) {
                it.remove();
                break;
            }
        }
    }

    public boolean equals(SortedIntegerList other) {
        return this.list.equals(other.list);
    }

    public SortedIntegerList splitList() {
        int i = 0;
        ListIterator<Integer> it = this.list.listIterator();
        SortedIntegerList result = new SortedIntegerList(this.withRepeats);
        while (it.hasNext()) {
            if (i % 2 == 0) {
                result.list.addLast(it.next());
                it.previous();
                it.remove();
            }
            else {
                it.next();
            }
            i++;
        }
        return result;
    }

    public String toString() {
        StringBuilder builder = new StringBuilder();
        ListIterator it = list.listIterator();
        while (it.hasNext())
            builder.append(it.next() + " ");
        return builder.toString();
    }

    private void addWithRepeats(int value) {
        ListIterator<Integer> it = list.listIterator();
        boolean firstElementCheck = false;
        while (it.hasNext() && it.next() < value)
            firstElementCheck = true;
        if (firstElementCheck)
            it.add(value);
        else
            list.addFirst(value);
    }

    private void addNoRepeats(int value) {
        ListIterator <Integer> it = list.listIterator();
        boolean firstElementCheck = false;
        boolean repeatCheck = false;

        while (it.hasNext() && it.next() <= value) {
            it.previous();
            if (it.next() == value)
                repeatCheck = true;
            firstElementCheck = true;
        }

        if (repeatCheck)
            return;

        if (firstElementCheck)
            it.add(value);
        else
            list.addFirst(value);
    }

}
