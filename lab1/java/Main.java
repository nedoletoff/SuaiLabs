import java.io.IOException;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) throws IOException {
        Scanner in = new Scanner(System.in);
        System.out.println("Enter the input file name:");
        String inputFile = in.nextLine();
        System.out.println("Enter the output file name:");
        String outputFile = in.nextLine();
        System.out.println("Enter the key");
        String key = in.nextLine();
        System.out.println("Enter the true to encrypt, Enter the false to decrypt");
        boolean flag = in.nextBoolean();
        IdeaFileEncryption.cryptFile(inputFile, outputFile,
                key, flag, IdeaFileEncryption.Mode.ECB);
    }
}
