package transcriptWriter;

import java.io.*;
import java.util.HashMap;

public class TranscriptWritter {
    public static void main(String[] args) {
        if (args.length != 2) {
            throw new RuntimeException("Invalid input");
        }

        HashMap<Character, String> transcriptions = new HashMap<>();
        transcriptions.put('а', "a");  transcriptions.put('А', "A");
        transcriptions.put('б', "b"); transcriptions.put('Б', "B");
        transcriptions.put('в', "v"); transcriptions.put('В', "V");
        transcriptions.put('г', "g"); transcriptions.put('Г', "G");
        transcriptions.put('д', "d"); transcriptions.put('Д', "D");
        transcriptions.put('е', "e"); transcriptions.put('Е', "E");
        transcriptions.put('ё', "yo"); transcriptions.put('Ё', "Yo");
        transcriptions.put('ж', "zh"); transcriptions.put('Ж', "Zh");
        transcriptions.put('з', "z"); transcriptions.put('З', "Z");
        transcriptions.put('и', "i"); transcriptions.put('И', "I");
        transcriptions.put('й', "y"); transcriptions.put('Й', "Y");
        transcriptions.put('к', "k"); transcriptions.put('К', "K");
        transcriptions.put('л', "l"); transcriptions.put('Л', "L");
        transcriptions.put('м', "m"); transcriptions.put('М', "M");
        transcriptions.put('н', "n"); transcriptions.put('Н', "N");
        transcriptions.put('о', "o"); transcriptions.put('О', "O");
        transcriptions.put('п', "p"); transcriptions.put('П', "P");
        transcriptions.put('р', "r"); transcriptions.put('Р', "R");
        transcriptions.put('с', "s"); transcriptions.put('С', "S");
        transcriptions.put('т', "t"); transcriptions.put('Т', "T");
        transcriptions.put('у', "u"); transcriptions.put('У', "U");
        transcriptions.put('ф', "f"); transcriptions.put('Ф', "F");
        transcriptions.put('х', "kh"); transcriptions.put('Х', "Kh");
        transcriptions.put('ц', "ts"); transcriptions.put('Ц', "Ts");
        transcriptions.put('ч', "ch"); transcriptions.put('Ч', "Ch");
        transcriptions.put('ш', "sh"); transcriptions.put('Ш', "Sh");
        transcriptions.put('щ', "shch"); transcriptions.put('Щ', "Shch");
        transcriptions.put('ъ', "\""); transcriptions.put('Ъ', "\"");
        transcriptions.put('ы', "y"); transcriptions.put('Ы', "Y");
        transcriptions.put('ь', "'"); transcriptions.put('Ь', "'");
        transcriptions.put('э', "e"); transcriptions.put('Э', "E");
        transcriptions.put('ю', "yu"); transcriptions.put('Ю', "Yu");
        transcriptions.put('я', "ya"); transcriptions.put('Я', "Ya");

        try {
            FileReader in = new FileReader(args[0]);
            FileWriter out = new FileWriter(args[1]);
            BufferedReader bfr = new BufferedReader(in);
            BufferedWriter bfw = new BufferedWriter(out);

            String line;
            StringBuilder res = new StringBuilder();
            while ((line = bfr.readLine()) != null) {
                for(char c : line.toCharArray()) {
                    if (transcriptions.containsKey(c))
                        res.append(transcriptions.get(c));
                    else
                        res.append(c);
                }
                res.append("\n");
            }
            bfw.write(res.toString());
            bfw.flush();
            bfw.close();
            bfr.close();
        } catch (IOException ioException) {
            System.out.println(ioException);
        }
    }
}
