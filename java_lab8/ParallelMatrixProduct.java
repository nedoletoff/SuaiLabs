public class ParallelMatrixProduct {
    int threadsNum;
    
    public ParallelMatrixProduct(int threadsNum) {
        this.threadsNum = threadsNum;
    }
    
    public UsualMatrix product(UsualMatrix a, UsualMatrix b) {
        if (a.getColumnsNum() != b.getRowsNum()) {
            throw new MyException("matrix cannot be produced");
        }
        UsualMatrix result = new UsualMatrix(a.getRowsNum(), b.getColumnsNum());
        Worker[] workers = new Worker[threadsNum];
        int numForOneThread;
        int numRows = 0;

        for (int i = 0; i < threadsNum; i++) {
            if (i < threadsNum -1)
                numForOneThread = (result.getRowsNum() / threadsNum);
            else
                numForOneThread = (result.getRowsNum() / threadsNum) +
                        result.getRowsNum() % threadsNum;
            workers[i] = new Worker(numRows, numRows+=numForOneThread,
                    a, b, result);
            workers[i].start();
        }

        for (Worker worker : workers) {
            try {
                worker.join();
            }
            catch (InterruptedException exception) {
                System.out.println(exception);
            }
        }

        return result;
    }

    private static class Worker extends Thread {

        private final int start;
        private final int stop;
        private final UsualMatrix matrixA;
        private final UsualMatrix matrixB;
        private UsualMatrix result;

        public Worker(int start, int stop, UsualMatrix a,
                      UsualMatrix b, UsualMatrix result) {
            super();
            this.start = start;
            this.stop = stop;
            this.matrixA = a;
            this.matrixB = b;
            this.result = result;
        }

        @Override
        public void run() {
            for (int i = start; i < stop; i++) {
                for (int j = 0; j < matrixB.getColumnsNum(); j++) {
                    int sum = 0;
                    for (int k = 0; k < matrixA.getColumnsNum(); k++) {
                        sum += matrixA.getElement(i, k) * matrixB.getElement(k, j);
                    }
                    result.setElement(i, j, sum);
                }
            }
        }
    }
}
    
    
