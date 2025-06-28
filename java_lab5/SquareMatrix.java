public class SquareMatrix extends UsualMatrix implements IMatrix {
    final int size;

   public SquareMatrix(int size) throws MyException {
       super(size, size);
       this.size = size;
       for (int i = 0; i < size; i++)
               this.setElement(i, i, 1);
   }

   public SquareMatrix(SquareMatrix other) throws MyException {
       super(other);
       this.size = other.size;
   }
    
   public int getSize() {
       return this.size;
   }

   public SquareMatrix sum(SquareMatrix other) throws MyException {
       if (this.getSize() != other.getSize())
           throw new MyException("matrix size are not same");

       SquareMatrix result = new SquareMatrix(this.size);

       for (int i = 0; i < size; i++)
           for (int j = 0; j < size; j++)
               result.setElement(i, j, other.getElement(i, j) + this.getElement(i, j));

       return result;
   }
}



