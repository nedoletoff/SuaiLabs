package dop;

import java.util.concurrent.TimeUnit;

public class Main {
    public static void main(String[] args) throws InterruptedException {
        final int n = 2000;
        int start = 2;
        int gap = 100;
        int stop = 100;
        TaskQueue queue = new TaskQueue();
        MyTask[] tasks = new MyTask[n];
        Worker[] workers = new Worker[3];


        for (int i = 0; i < n; i++) {
            tasks[i] = new MyTask(start, stop);
            start = stop + 1;
            stop = gap * (i + 2);
        }

        for (MyTask task : tasks)
            queue.push(task);

        for (int i = 0 ; i < 3; i++) {
            workers[i] = new Worker(queue);
            workers[i].start();
            queue.showResults();
            System.out.println();
        }

        for (Worker worker : workers)
            worker.join();

        queue.showResults();


        //task1.run();
        //System.out.println(task1.getAnswers().toString());

    }
}

