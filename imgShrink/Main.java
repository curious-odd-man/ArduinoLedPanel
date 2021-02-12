package sample;

import java.io.File;
import java.io.IOException;

public class Main {
    public static void main(String[] args) throws IOException {
        Controller controller = new Controller();
        controller.parseFile(new File("Test.bmp"));
    }
}
