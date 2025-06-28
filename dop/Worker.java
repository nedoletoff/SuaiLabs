package dop;

import javax.lang.model.type.NullType;
import java.util.LinkedList;
import java.util.NoSuchElementException;

public class Worker extends Thread {
    TaskQueue queue;
    LinkedList<Integer> results;

    public Worker(TaskQueue queue) {
        this.queue = queue;
        this.results = queue.getResults();
    }

    @Override
    public void run() {
        MyTask task;
        boolean notEmpty = true;
        while (notEmpty) {
            try {
                task = queue.pop();
            } catch (NoSuchElementException exception) {
                notEmpty = false;
                break;
            }
            task.run();
            synchronized (results) {
                results.addAll(task.getAnswers());
            }
        }
    }
}
