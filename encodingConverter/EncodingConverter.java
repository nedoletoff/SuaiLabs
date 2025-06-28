package encodingConverter;

import java.io.*;
import java.nio.charset.Charset;

public class EncodingConverter {
    public static void main(String[] args) {
        if (args.length != 4) {
            throw new RuntimeException("Invalid input");
        }

        Charset encodingIn = Charset.forName(args[2]);
        Charset encodingOut = Charset.forName(args[3]);
        try {
            FileReader in = new FileReader(args[0], encodingIn);
            FileWriter out = new FileWriter(args[1], encodingOut);
            BufferedReader bfr = new BufferedReader(in);
            BufferedWriter bfw = new BufferedWriter(out);

            String line;
            while ((line = bfr.readLine()) !=  null) {
                bfw.write(line);
                bfw.newLine();
            }

            bfw.flush();
            bfw.close();
            bfr.close();
        }
        catch (IOException ioException) {
            System.out.println(ioException);
        }
    }
}

