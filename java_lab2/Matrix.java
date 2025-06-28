import java.lang.StringBuilder;

public class Matrix {
    int[][] matrix;
    int size;

    public Matrix(int size) throws Exception {
        if (size <= 1)
            throw new Exception("size <= 1");
        this.size = size;
        this.matrix = new int[size][size];
        for (int i = 0; i < this.size; i++)
            for (int j = 0; j < this.size; j++)
                this.matrix[i][j] = 1;
    }

    public Matrix(Matrix other) {
        this.size = other.size;
        this.matrix = new int[size][size];
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                this.matrix[i][j] = other.matrix[i][j];
    }

    public void setElement(int row, int column, int value) throws Exception {
        if (row >= this.size)
            throw new Exception("row >= size");
        if (column >= size)
            throw new Exception("column >= size");
        if (row < 0)
            throw new Exception("row < 0");
        if (column < 0)
            throw new Exception("column < 0");

        this.matrix[row][column] = value;
    }

    public int getElement(int row, int column) throws Exception {
        if (row >= this.size)
            throw new Exception("row >= size, size");
        if (column >= this.size)
            throw new Exception("column >= size");
        if (row < 0)
            throw new Exception("row < 0");
        if (column < 0)
            throw new Exception("column < 0");

        return this.matrix[row][column];
    }

    public Matrix sum(Matrix other) throws Exception {
        if (this.size != other.size)
            throw new Exception("matrix sizes are not the same");

        Matrix result = new Matrix(this);

        for (int i = 0; i < this.size; i++)
            for (int j = 0; j < this.size; j++)
                result.matrix[i][j] += other.matrix[i][j];

        return result;
    }

    public Matrix product(Matrix other) throws Exception {
        if (this.size != other.size)
            throw new Exception("matrix sizes are not the same");

        Matrix result = new Matrix(this.size);

        for (int i = 0; i < this.size; i++)
            for (int j = 0; j < this.size; j++) {
                result.matrix[i][j] = 0;
                for (int k = 0; k < this.size; k++)
                    result.matrix[i][j] += this.matrix[i][k] * other.matrix[k][j];
            }

        return result;
    }

    public String toString() {
        StringBuilder builder = new StringBuilder();

        for (int i = 0; i < this.size; i++) {
            for (int j = 0; j < this.size; j++) {
                builder.append(this.matrix[i][j]);
                builder.append(" ");
            }
            builder.append("\n");
        }

        String result = builder.toString();
        return result;
    }

    public void sort() {
        int[] columnSum = new int[size];
        for (int i = 0; i < size; i++) {
            columnSum[i] = 0;
            for (int j = 0; j < size; j++) 
                columnSum[i] += this.matrix[j][i] * this.matrix[j][i];
        }
        
        int min;
        int minNum;
        for (int i = 0; i < size; i++) {
            min = columnSum[i];
            minNum = i;
            for (int j = i + 1; j < size; j++) 
                if (columnSum[j] < min) {
                    min = columnSum[j];
                    minNum = j;
                }
            int temp = columnSum[i];
            columnSum[i] = min;
            columnSum[minNum] = temp;
            this.changeColumns(minNum, i);
        }
    }

    void changeColumns(int a, int b) {
        int temp;
        for (int i = 0; i < size; i++) {
            temp = matrix[i][a];
            matrix[i][a] = matrix[i][b];
            matrix[i][b] = temp;
        }
    }




}


        



