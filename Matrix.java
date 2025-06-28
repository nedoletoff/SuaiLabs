import java.lang.StringBuilder;

public class Matrix {
    protected int[][] matrix;
    protected int rowsNum;
    protected int columnsNum;


    public Matrix(int rowsNum, int columnsNum) throws MyException {
        if (rowsNum < 0)
            throw new MyException("rowsNum <= 0");
        if (columnsNum < 0)
            throw new MyException("columnsNum <= 0");
        this.rowsNum = rowsNum;
        this.columnsNum = columnsNum;
        this.matrix = new int[rowsNum][columnsNum];
    }

    public Matrix(Matrix other) {
        this.rowsNum = other.rowsNum;
        this.columnsNum = other.columnsNum;
        this.matrix = new int[rowsNum][columnsNum];
        for (int i = 0; i < rowsNum; i++)
            for (int j = 0; j < columnsNum; j++)
                this.setElement(i, j, other.getElement(i, j));
    }

    public void setElement(int row, int column, int value) throws MyException {
        if (row >= this.getRowsNum())
            throw new MyException("row >= rowsNum");
        if (column >= getColumnsNum())
            throw new MyException("column >= columnsNum");
        if (row < 0)
            throw new MyException("row < 0");
        if (column < 0)
            throw new MyException("column < 0");

        this.matrix[row][column] = value;
    }

    public int getElement(int row, int column) throws MyException {
        if (row >= this.getRowsNum())
            throw new MyException("row >= rowsNum");
        if (column >= getColumnsNum())
            throw new MyException("column >= columnsNum");
        if (row < 0)
            throw new MyException("row < 0");
        if (column < 0)
            throw new MyException("column < 0");

        return this.matrix[row][column];
    }

    public int getRowsNum() {
        return this.rowsNum;
    }

    public int getColumnsNum() {
        return this.columnsNum;
    }

    public Matrix sum(Matrix other) throws MyException {
        if (this.getRowsNum() != other.getRowsNum() || this.getColumnsNum() != other.getColumnsNum())
            throw new MyException("matrix sizes are not the same");

        Matrix result = new Matrix(this);

        for (int i = 0; i < this.getRowsNum(); i++)
            for (int j = 0; j < this.getColumnsNum(); j++) 
                result.setElement(i, j, result.getElement(i, j)  + other.getElement(i, j));

        return result;
    }

    public Matrix product(Matrix other) throws MyException {
        if (this.getColumnsNum() != other.getRowsNum())
            throw new MyException("matrix cannot be myltiplied");

        Matrix result = new Matrix(this.getRowsNum(), other.getColumnsNum());

        for (int m = 0; m < result.getRowsNum(); m++)
            for (int k = 0; k < result.getColumnsNum(); k++) {
                result.setElement(m, k, 0);
                for (int n = 0; n < result.getRowsNum(); n++)
                    result.setElement(m, k, result.getElement(m, k) + 
                    this.getElement(m, n) * other.getElement(n, k));
            }

        return result;
    }

    public String toString() {
        StringBuilder builder = new StringBuilder();

        for (int i = 0; i < this.getRowsNum(); i++) {
            for (int j = 0; j < this.getColumnsNum(); j++) {
                builder.append(this.getElement(i, j));
                builder.append(" ");
            }
            builder.append("\n");
        }

        return builder.toString();
    }
    
    public boolean equals(Matrix other) {
        if (this.getRowsNum() != other.getRowsNum() || this.getColumnsNum() != other.getColumnsNum())
            return false;
        for (int i = 0; i < this.getRowsNum(); i++)
            for (int j = 0; j < this.getColumnsNum(); j++)
                if (this.getElement(i, j) != other.getElement(i, j))
                    return false;
        return true;
    }
}



        



