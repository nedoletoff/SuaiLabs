import java.util.*;
public class Main {
    public static void main(String[] args) {
        Random random = new Random();
        int matrixSize = 1000;
        IMatrix aSparse = new SparseMatrix(matrixSize, matrixSize);
        IMatrix bSparse = new SparseMatrix(matrixSize, matrixSize);
        for (int i = 0; i < matrixSize; i++) {
            aSparse.setElement(random.nextInt(matrixSize),
                    random.nextInt(matrixSize),
                    random.nextInt(1000) - 500);
        }
        for (int i = 0; i < matrixSize; i++) {
            bSparse.setElement(random.nextInt(matrixSize),
                    random.nextInt(matrixSize),
                    random.nextInt(1000) - 500);
        }
        IMatrix aUsual = new UsualMatrix(aSparse);
        IMatrix bUsual = new UsualMatrix(bSparse);
        IMatrix resultSparse = aSparse.sum(bSparse);
        IMatrix resultUsual =  aUsual.sum(bUsual);

        System.out.println(resultSparse.equals(resultUsual));
        //System.out.println(resultUsual);
        //System.out.println(resultSparse);
    }
}

