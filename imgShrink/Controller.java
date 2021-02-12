package sample;

import javax.imageio.ImageIO;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.IntStream;

import static java.awt.image.BufferedImage.TYPE_INT_RGB;

public class Controller {

    private static final int     TARGET_WIDTH  = 190;
    private static final int     TARGET_HEIGHT = 280;
    private static final boolean LETTERS_BOXES = false;
    private static final boolean COLORED       = false;

    private static Path          outputPath      = Paths.get("output.txt");
    private static Path          outputImagePath = Paths.get("output.png");
    private static StringBuilder aStringBuilder  = new StringBuilder();

    public void parseFile(File file) throws IOException {
        BufferedImage read = ImageIO.read(file);
        System.out.println("Original image size = " + read.getHeight() + "x" + read.getWidth());
        if (LETTERS_BOXES) {
            List<BufferedImage> lines = splitByLines(read);
            for (BufferedImage line : lines) {
                List<BufferedImage> letters = splitByLetters(line);
                for (BufferedImage letter : letters) {
                    processLetter(letter, true);
                    BufferedImage bufferedImage = shrinkImageJava(letter);
                    processLetter(bufferedImage, false);
                }
            }
        } else {
            customShrinkColoredImage(read);
        }

        Files.write(outputPath, aStringBuilder.toString()
                                              .getBytes(), StandardOpenOption.TRUNCATE_EXISTING, StandardOpenOption.CREATE);
    }

    private static void customShrinkColoredImage(BufferedImage image) {
        double dx = ((double) image.getWidth()) / TARGET_WIDTH;
        double dy = ((double) image.getHeight()) / TARGET_HEIGHT;
        int[][] arr = new int[TARGET_HEIGHT][TARGET_WIDTH];
        for (int j = 0; j < arr.length; j++) {
            for (int i = 0; i < arr[j].length; i++) {
                System.out.print(",");
                arr[j][i] = getRegionColor(image, i, j, dx, dy);
            }
            System.out.println();
        }

        createImageFile(arr, 10);
    }

    private static void createImageFile(int[][] arr, int pixelPerDot) {
        BufferedImage outputImage = new BufferedImage(TARGET_WIDTH,
                                                      TARGET_HEIGHT, TYPE_INT_RGB);

        // scales the input image to the output image
        Graphics2D g2d = outputImage.createGraphics();
        for (int i = 0; i < arr.length; i++) {
            for (int j = 0; j < arr[i].length; j++) {
                System.out.print(".");
                g2d.setPaint(new Color(arr[i][j]));
                g2d.drawRect(i * pixelPerDot, j * pixelPerDot, pixelPerDot, pixelPerDot);
            }
            System.out.println();
        }

        g2d.dispose();

        try {
            ImageIO.write(outputImage, "bmp", outputImagePath.toFile());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static int getRegionColor(BufferedImage image, int x, int y, double dx, double dy) {
        double startX = x * dx;
        double startY = y * dy;
        BufferedImage region = image.getSubimage((int) startX, (int) startY, (int) dx, (int) dy);

        class RGB {
            public long r;
            public long g;
            public long b;

            public RGB add(RGB other) {
                r += other.r;
                g += other.g;
                b += other.b;
                return this;
            }

            public int avg(int cnt) {
                r /= cnt;
                g /= cnt;
                b /= cnt;
                r <<= 16;
                g <<= 8;

                return (int) (0xFF000000 | r | g | b);
            }
        }

        RGB reduce = IntStream.range(0, region.getHeight())
                              .boxed()
                              .flatMap(i -> IntStream.range(0, region.getWidth())
                                                     .mapToObj(j -> {
                                                         RGB rgb = new RGB();
                                                         int irgb = region.getRGB(j, i);
                                                         rgb.r = (irgb & 0xFF0000) >> 16;
                                                         rgb.g = (irgb & 0x00FF00) >> 8;
                                                         rgb.b = irgb & 0x0000FF;
                                                         return rgb;
                                                     }))
                              .reduce(new RGB(), RGB::add);

        return reduce.avg(image.getHeight() * image.getWidth());
    }

    private static BufferedImage shrinkImageJava(BufferedImage inputImage) {
        BufferedImage outputImage = new BufferedImage(TARGET_WIDTH,
                                                      TARGET_HEIGHT, inputImage.getType());

        // scales the input image to the output image
        Graphics2D g2d = outputImage.createGraphics();
        g2d.drawImage(inputImage, 0, 0, TARGET_WIDTH, TARGET_HEIGHT, null);
        g2d.dispose();
        return outputImage;
    }

    private static List<BufferedImage> splitByLetters(BufferedImage image) {
        List<BufferedImage> letters = new ArrayList<>();

        boolean prevWhiteLine = true;
        int colStart = 0;
        for (int x = 0; x < image.getWidth(); x++) {
            boolean currWhitLine = isPixelColWhite(image, x);
            if (currWhitLine != prevWhiteLine) {
                if (!prevWhiteLine) {
                    //System.out.println("Found column: " + colStart + " to " + x);
                    letters.add(image.getSubimage(colStart, 0, x - colStart + 1, image.getHeight()));
                }
                colStart = x;
                prevWhiteLine = currWhitLine;
            }
        }
        return letters;
    }

    private static boolean isPixelColWhite(BufferedImage image, int x) {
        return IntStream.range(0, image.getHeight())
                        .mapToObj(i -> image.getRGB(x, i))
                        .allMatch(clr -> (clr & 0xFFFFFF) == 0xFFFFFF);
    }

    private static boolean isPixelLineWhite(BufferedImage image, int y) {
        return IntStream.range(0, image.getWidth())
                        .mapToObj(i -> image.getRGB(i, y))
                        .allMatch(clr -> (clr & 0xFFFFFF) == 0xFFFFFF);
    }

    private static List<BufferedImage> splitByLines(BufferedImage image) {
        List<BufferedImage> lines = new ArrayList<>();
        boolean prevWhiteLine = true;
        int lineStart = 0;
        for (int y = 0; y < image.getHeight(); y++) {
            boolean currWhitLine = isPixelLineWhite(image, y);
            if (currWhitLine != prevWhiteLine) {
                if (!prevWhiteLine) {
                    //System.out.println("Found line: " + lineStart + " to " + y);
                    lines.add(image.getSubimage(0, lineStart, image.getWidth(), y - lineStart + 1));
                }
                lineStart = y;
                prevWhiteLine = currWhitLine;
            }
        }
        return lines;
    }

    private void processLetter(BufferedImage read, boolean doBound) {
        BufferedImage image = read;
        if (doBound) {
            image = getBoundedContents(read);
        }
        drawImage(image);

        //System.out.println("Bounded image size = " + image.getHeight() + "x" + image.getWidth());
        boolean[][] booleans = shrinkToSize(TARGET_WIDTH, TARGET_HEIGHT, image);

        for (boolean[] aBoolean : booleans) {
            for (boolean b : aBoolean) {
                if (b) {
                    System.out.print('*');
                } else {
                    System.out.print(" ");
                }
            }
            System.out.println();
        }

        printAsCode("letter", booleans);
    }

    private void printAsCode(String letter, boolean[][] booleans) {
        aStringBuilder.append("// Letter " + letter)
                      .append("{\n");
        for (boolean[] aBoolean : booleans) {
            aStringBuilder.append("    0b");
            for (boolean b : aBoolean) {
                if (b) {
                    aStringBuilder.append('1');
                } else {
                    aStringBuilder.append('0');
                }
            }
            aStringBuilder.append(",\n");
        }
        aStringBuilder.append("}\n");
    }

    private static void drawImage(BufferedImage image) {
        for (int y = 0; y < image.getHeight(); y++) {
            for (int x = 0; x < image.getWidth(); x++) {
                int clr = 0x00FFFFFF & image.getRGB(x, y);
                if (clr == 0x00FFFFFF) {
                    System.out.print(' ');
                } else {
                    System.out.print('#');
                }
            }
            System.out.println();
        }
    }

    private boolean[][] shrinkToSize(int x, int y, BufferedImage image) {
        double dx = ((double) image.getWidth()) / x;
        double dy = ((double) image.getHeight()) / y;
        boolean[][] arr = new boolean[y][x];
        //System.out.println("Shrink by: " + dx + "x" + dy);
        for (int j = 0; j < arr.length; j++) {
            for (int i = 0; i < arr[j].length; i++) {
                arr[j][i] = isBlack(image, i, j, dx, dy);
            }
        }

        return arr;
    }

    private boolean isBlack(BufferedImage image, int x, int y, double dx, double dy) {
        double startX = x * dx;
        double startY = y * dy;

//        System.out.println("Bounded image size = " + image.getWidth() + ":" + image.getHeight());
//        System.out.println("Region size = " + startX + ":" + startY + " " + (startX + dx) + ":" + (startY + dy));
        BufferedImage region = image.getSubimage((int) startX, (int) startY, (int) dx, (int) dy);
        //drawImage(region);

        int white = 0;
        int black = 0;

        for (int i = 0; i < region.getHeight(); i++) {
            for (int j = 0; j < region.getWidth(); j++) {
                int clr = 0x00FFFFFF & region.getRGB(j, i);
                if (clr == 0x00FFFFFF) {
                    white++;
                } else {
                    black++;
                }
            }
        }

        //System.out.println("decision " + white + " vs " + black + " = " + (black >= white));

        return black >= white;
    }

    private BufferedImage getBoundedContents(BufferedImage image) {
        int minX = image.getWidth();
        int minY = image.getHeight();
        int maxX = 0;
        int maxY = 0;
        for (int y = 0; y < image.getHeight(); y++) {
            for (int x = 0; x < image.getWidth(); x++) {
                int clr = 0x00FFFFFF & image.getRGB(x, y);
                if (clr != 0x00FFFFFF) {
                    if (minX > x) {
                        minX = x;
                    }

                    if (minY > y) {
                        minY = y;
                    }

                    if (maxX < x) {
                        maxX = x;
                    }

                    if (maxY < y) {
                        maxY = y;
                    }
                }
            }
        }
        System.out.println("Subimaging = " + minX + "/" + minY + "/" + maxX + "/" + maxY);
        return image.getSubimage(minX, minY, maxX - minX + 1, maxY - minY + 1);
    }
}
