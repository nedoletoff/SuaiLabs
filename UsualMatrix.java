public class UsualMatrix extends Matrix implements IMatrix {
    protected int[][] matrix;
    protected int rowsNum;
    protected int columnsNum;

    public UsualMatrix(int rowsNum, int columnsNum) throws MyException {
        if (rowsNum < 0)
            throw new MyException("rowsNum < 0");
        if (columnsNum < 0)
            throw new MyException("columnsNum < 0");
        this.rowsNum = rowsNum;
        this.columnsNum = columnsNum;
        this.matrix = new int[rowsNum][columnsNum];
    }

    public UsualMatrix(IMatrix other) {
        this.rowsNum = other.getRowsNum();
        this.columnsNum = other.getColumnsNum();
        this.matrix = new int[rowsNum][columnsNum];
        for (int i = 0; i < rowsNum; i++)
            for (int j = 0; j < columnsNum; j++)
                this.setElement(i, j, other.getElement(i, j));
    }

    public int getRowsNum() {
        return rowsNum;
    }

    public int getColumnsNum() {
        return columnsNum;
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

    public IMatrix sum(IMatrix other) throws MyException {
        if (this.getRowsNum() != other.getRowsNum() || this.getColumnsNum() != other.getColumnsNum())
            throw new MyException("matrix sizes are not the same");

        IMatrix result = new UsualMatrix(this.getRowsNum(), this.getColumnsNum());

        for (int i = 0; i < this.getRowsNum(); i++)
            for (int j = 0; j < this.getColumnsNum(); j++)
                result.setElement(i, j, this.getElement(i, j) + other.getElement(i, j));

        return result;
    }

    public IMatrix product(IMatrix other) throws MyException {
        if(this.getColumnsNum() !=other.getRowsNum())
            throw new MyException("matrix cannot be produced");
        IMatrix result = new UsualMatrix(this.getRowsNum(), other.getColumnsNum());

        for(int m = 0; m<result.getRowsNum();m++)
            for(int k = 0; k<result.getColumnsNum();k++)
            {
                result.setElement(m, k, 0);
                for (int n = 0; n < result.getRowsNum(); n++)
                    result.setElement(m, k, result.getElement(m, k) +
                            this.getElement(m, n) * other.getElement(n, k));
            }
        return result;
    }
}



        



