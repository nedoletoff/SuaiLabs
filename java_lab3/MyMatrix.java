class MyMatrix extends Matrix {

    public MyMatrix(int rowsNum, int columnsNum) throws MyException {
        super(1, 1);
        this.rowsNum = rowsNum;
        this.columnsNum = columnsNum;
    }

    public MyMatrix(MyMatrix other) {
        this(other.getRowsNum(), other.getColumnsNum());
        this.setElement(0, 0, other.getElement(0, 0));
    }

    @Override
    public void setElement(int row, int column, int value) throws MyException {
        if (row >= this.getRowsNum())
            throw new MyException("row >= rowsNum");
        if (column >= getColumnsNum())
            throw new MyException("column >= columnsNum");
        if (row < 0)
            throw new MyException("row < 0");
        if (column < 0)
            throw new MyException("column < 0");

        matrix[0][0] = value - column - row * this.getColumnsNum();
    }

    @Override
    public int getElement(int row, int column) throws MyException {
        if (row >= this.getRowsNum())
            throw new MyException("row >= rowsNum");
        if (column >= getColumnsNum())
            throw new MyException("column >= columnsNum");
        if (row < 0)
            throw new MyException("row < 0");
        if (column < 0)
            throw new MyException("column < 0");

        return matrix[0][0] + column + row * this.getColumnsNum();
    }
}


