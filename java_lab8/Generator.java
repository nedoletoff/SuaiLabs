import java.lang.reflect.GenericDeclaration;
import java.util.Arrays;
import java.util.LinkedList;

public class Generator {
    int n;
    int k;
    int threadsNum;
    Integer[] currentArray;
    LinkedList<Integer[]> arrays;
    Worker[] workers;

    public Generator(int n, int k, int threadsNum) {
        this.n = n;
        this.k = k;
        this.threadsNum = threadsNum;
        this.currentArray = new Integer[k];
        this.arrays = new LinkedList<Integer[]>();
        for (int i = 0; i < k; i++)
            currentArray[i] = 1;


    }

    public int getResult() {
        return arrays.size();
    }

    public void usualGenerate() {
        usualGenerate(0);
    }

    public void printArrays() {
        for (Integer[] integers : arrays) {
            System.out.print("{");
            for (Integer integer : integers)
                System.out.print(integer.toString() + " ");
            System.out.println("\b}");
        }
    }

    public void clearArrays() {
        arrays.clear();
    }

    public void parallelGenerate() {
        int resultNum = (int) Math.pow(n, k);
        int forOneThread = resultNum / threadsNum;
        int rest = resultNum % threadsNum;
        int start = 0;
        workers = new Worker[threadsNum];

        for (int i = 0; i < threadsNum - 1; i++) {
            setNumber(currentArray, start);
            workers[i] = new Worker(forOneThread, currentArray, this);
            start += forOneThread;
        }
        setNumber(currentArray, start);
        workers[threadsNum-1] = new Worker(forOneThread + rest, currentArray,
                this);

        for (Worker worker : workers)
            worker.start();
        for (Worker worker : workers)
            try {
                worker.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
    }

    private void usualGenerate(int current) {
        if (current < k)
            for (int j = 1; j <= n; j++) {
                currentArray[current] = j;
                usualGenerate(current+1);
            }
        else
            arrays.add(currentArray.clone());
    }

    private void getNextNumber(Integer[] currentArray) {
        for (int i = k- 1; i >= 0; i--) {
            if (currentArray[i]++ < n) {
                break;
            }
            currentArray[i] = 1;
        }
    }

    private void setNumber(Integer[] currentArray, int number) {
        int degree = k;
        for (int i = 0; i < k; i++) {
            currentArray[i] = number / (int) Math.pow(n, --degree) + 1;
            number = number %  (int) Math.pow(n, degree);
        }
    }

    private static class Worker extends Thread {
        private final int stop;
        private final Integer[] currentArray;
        private final Generator generator;
        private final LinkedList<Integer[]> arrays;


        public Worker(int stop, Integer[] currentArray, Generator generator) {
            super();
            this.stop = stop;
            this.currentArray = currentArray.clone();
            this.generator = generator;
            this.arrays = new LinkedList<>();
        }

        @Override
        public void run() {
            for (int i = 0; i < stop; i++) {
                generator.getNextNumber(currentArray);
                arrays.add(currentArray.clone());
            }
            synchronized (generator.arrays) {
                generator.arrays.addAll(arrays);
            }
        }
    }
}
