import java.lang.StringBuilder;
public abstract class Matrix implements IMatrix {
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
}



        



