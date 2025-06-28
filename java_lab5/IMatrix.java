interface IMatrix {
    void setElement(int row, int column, int value);
    int getElement(int row, int column);
    int getRowsNum();
    int getColumnsNum();
    IMatrix sum(IMatrix other);
    IMatrix product(IMatrix other);
    String toString();

    default boolean equals(IMatrix other) {
         if (this.getRowsNum() !=other.getRowsNum()
                || this.getColumnsNum() != other.getColumnsNum())
            return false;
        for (int i = 0; i < this.getRowsNum(); i++)
            for (int j = 0; j < this.getColumnsNum(); j++)
                if (this.getElement(i, j) != other.getElement(i, j))
                    return false;
        return true;
    }

}



