package dop;

import java.util.ArrayList;

public class MyTask {
    private int start;
    private int stop;
    private ArrayList<Integer> answers;

    public MyTask(int start, int stop) {
        this.start = start;
        this.stop = stop;
        this.answers = new ArrayList<>();
    }

    public void setStart(int start) {
        this.start = start;
    }

    public void setStop(int stop) {
        this.stop = stop;
    }

    public ArrayList<Integer> getAnswers() {
        return answers;
    }

    public int getStart() {
        return start;
    }

    public int getStop() {
        return stop;
    }

    public void run(){
        boolean flag;
        for (int i = start; i < stop; i++) {
            flag = true;
            for (int j = 2; j < (int) Math.sqrt(i); j++)
                if (i % j == 0) {
                    flag = false;
                    break;
                }
            if (flag)
                answers.add(i);
        }
        answers.add(0);
    }
}
