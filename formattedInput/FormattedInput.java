package formattedInput;

import java.util.LinkedList;
import java.util.Scanner;

public class FormattedInput {
    public static Object[] scanf(String format) throws Exception {
        Scanner scanner = new Scanner(System.in);
        while (true) {
            System.out.println("Input data: ");
            String input = scanner.nextLine();
            try {
                return sscanf(format, input);
            } catch (Exception exception) {
                if (exception.toString().equals("Wrong format"))
                    throw exception;
                System.out.println(exception);
            }
        }
    }

    public static Object[] sscanf(String format, String in) throws Exception {
        LinkedList<Object> result = new LinkedList<Object>();
        String[] inputs = in.split(" ");
        String[] formats = format.split(" ");

        if (inputs.length != formats.length)
            throw new Exception("Invalid input");

        for (int i = 0; i < inputs.length; i++) {
            switch (formats[i]) {
                case "%d" -> {
                    try {
                        result.add(Integer.valueOf(inputs[i]));
                    } catch (NumberFormatException exception) {
                        throw new Exception("Invalid input");
                    }
                }

                case "%f" -> {
                try {
                    result.add(Double.valueOf(inputs[i]));
                }
                catch (NumberFormatException exception) {
                    throw new Exception("Invalid input");
                }
            }

                case "%s" -> result.add(inputs[i]);
                    case "%c" -> {
                        if (inputs[i].length() > 1)
                            throw new Exception("Invalid input");
                        else
                            result.add(inputs[i].charAt(0));
                    }

                default -> throw new Exception("Wrong format");

            }
        }
        return result.toArray();
    }
}
