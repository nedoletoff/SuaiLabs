import java.util.*;

public class SparseMatrix extends Matrix implements IMatrix {
    protected int rowsNum;
    protected int columnsNum;

    static class Row {
        int rowIndex;

        static class Element {
            int columnIndex;
            int value;

            Element(int columnIndex, int value) {
                this.columnIndex = columnIndex;
                this.value = value;
            }

            public String toString() {
                return "column[" + columnIndex + "] = " + value;
            }
        }

        ArrayList<Element> row;

        Row(int rowIndex, int columnIndex, int value) {
            this.rowIndex = rowIndex;
            Element el = new Element(columnIndex, value);
            this.row = new ArrayList<Element>();
            this.row.add(el);
        }

        public void addElement(int column, int value) {
            ListIterator<Row.Element> itRow = this.row.listIterator();
            while (itRow.hasNext() && itRow.next().columnIndex <= column) {
                itRow.previous();
                if (itRow.next().columnIndex == column) {
                    itRow.previous();
                    itRow.next().value = value;
                    return;
                }
            }
            if (this.row.size() != 0) {
                if (itRow.hasNext())
                    itRow.previous();
                else {
                    itRow.previous();
                    if (itRow.next().columnIndex > column)
                        itRow.previous();
                }
                itRow.add(new Element(column, value));
            } else {
                this.row.add(new Element(column, value));
            }
        }

        public String toString() {
            StringBuilder builder = new StringBuilder();
            builder.append("row[").append(rowIndex).append("] : ");
            for (Element element : row) builder.append(element).append(", ");
            return builder.toString();
        }
    }

    protected ArrayList<Row> matrix;

    public SparseMatrix(int rowsNum, int columnsNum) throws MyException {
        if (rowsNum <= 0)
            throw new MyException("rowsNum <= 0");
        if (columnsNum <= 0)
            throw new MyException("columnsNum <= 0");

        this.rowsNum = rowsNum;
        this.columnsNum = columnsNum;
        this.matrix = new ArrayList<Row>();
    }

    public SparseMatrix(SparseMatrix other) {
        this.rowsNum = other.rowsNum;
        this.columnsNum = other.columnsNum;
        this.matrix = new ArrayList<Row>(other.matrix);
    }

    public SparseMatrix(IMatrix other) {
        this(other.getRowsNum(), other.getColumnsNum());
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
        if (this.rowsNum <= row)
            throw new MyException("rowsNum <= rows");
        if (this.columnsNum <= column)
            throw new MyException("columnsNum <= column");
        if (rowsNum < 0)
            throw new MyException("rowsNum < 0");
        if (columnsNum < 0)
            throw new MyException("columnsNum < 0");

        if (value != 0)
            this.addElement(row, column, value);
        else
            this.removeElement(row, column);
    }

    public int getElement(int row, int column) throws MyException {
        ListIterator<Row> itMatrix = this.matrix.listIterator();
        boolean rowCheck = false;

        while (itMatrix.hasNext() && itMatrix.next().rowIndex <= row) {
            itMatrix.previous();
            if (itMatrix.next().rowIndex == row) {
                rowCheck = true;
                itMatrix.previous();
                break;
            }
        }
        if (rowCheck) {
            ListIterator<Row.Element> itRow = itMatrix.next().row.listIterator();
            while (itRow.hasNext() && itRow.next().columnIndex <= column) {
                itRow.previous();
                if (itRow.next().columnIndex == column) {
                    itRow.previous();
                    return itRow.next().value;
                }
            }
        }
        return 0;
    }

    public IMatrix sum(IMatrix other) throws MyException {
        if (this.getRowsNum() != other.getRowsNum() || this.getColumnsNum() != other.getColumnsNum())
            throw new MyException("matrix sizes are not the same");

        IMatrix result = new SparseMatrix(this.getRowsNum(), this.getColumnsNum());

        for (int i = 0; i < this.getRowsNum(); i++)
            for (int j = 0; j < this.getColumnsNum(); j++)
                result.setElement(i, j, this.getElement(i, j) + other.getElement(i, j));

        return result;
    }

    public IMatrix product(IMatrix other) throws MyException {
        if (this.getColumnsNum() != other.getRowsNum())
            throw new MyException("matrix cannot be product");
        IMatrix result = new SparseMatrix(this.getRowsNum(), other.getColumnsNum());

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
        for (Row row : matrix) builder.append(row).append("\n");
        return builder.toString();
    }

    private void addElement(int row, int column, int value) {
        ListIterator<Row> itMatrix = this.matrix.listIterator();
        boolean rowCheck = false;

        while (itMatrix.hasNext() && itMatrix.next().rowIndex <= row) {
            itMatrix.previous();
            if (itMatrix.next().rowIndex == row) {
                rowCheck = true;
                break;
            }
        }
        if (this.matrix.size() != 0) {
            if (rowCheck) {
                itMatrix.previous();
                itMatrix.next().addElement(column, value);
                return;
            } else if (itMatrix.hasNext())
                itMatrix.previous();
            else {
                itMatrix.previous();
                if (itMatrix.next().rowIndex > row)
                    itMatrix.previous();
            }
            itMatrix.add(new Row(row, column, value));
        } else {
            matrix.add(new Row(row, column, value));
        }
    }

    private void removeElement(int row, int column) {
        ListIterator<Row> itMatrix = this.matrix.listIterator();
        boolean rowCheck = false;

        while (itMatrix.hasNext() && itMatrix.next().rowIndex <= row) {
            itMatrix.previous();
            if (itMatrix.next().rowIndex == row) {
                rowCheck = true;
                break;
            }
        }
        if (rowCheck) {
            itMatrix.previous();
            ListIterator<Row.Element> itRow = itMatrix.next().row.listIterator();
            while (itRow.hasNext() && itRow.next().columnIndex <= column) {
                itRow.previous();
                if (itRow.next().columnIndex == column) {
                    itRow.previous();
                    itRow.remove();
                    break;
                }
            }
        }
    }
}

