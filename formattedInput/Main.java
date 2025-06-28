package formattedInput;

import java.util.Arrays;

public class Main {
    public static void main(String[] args) throws Exception {
        String in = "12 4 5.5 df ss l";
        String format = "%d %d %f %s %s %c";
        System.out.println(Arrays.toString(FormattedInput.sscanf(format, in)));

        System.out.println(Arrays.toString((FormattedInput.scanf(format))));
    }
}
