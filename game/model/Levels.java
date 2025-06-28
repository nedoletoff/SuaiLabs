package model;

import java.io.File;
import java.util.ArrayList;

public class Levels {
    ArrayList<String> filesName;
    File path;

    public Levels(String path) {
        filesName = new ArrayList<>();
        this.path = new File(path);
        File[] files = this.path.listFiles();
        assert files != null;
        for (File file : files) {
            filesName.add(file.getName());
        }
    }

    public void setPath(File path) {
        this.path = path;
    }

    public ArrayList<String> getFilesName() {
        return filesName;
    }

    public int getScores(String levelName) {
        return SavedLevel.load(levelName).bestPoints;
    }
    public int getTimer(String levelName) {
        return SavedLevel.load(levelName).bestTime;
    }

    public ArrayList<String> getLevelsNames() {
        ArrayList<String> res = new ArrayList<>();
        for (String name : filesName) {
            res.add(name.split("\\.")[0]);
        }
        System.out.println(res);
        return res;
    }

    public File getPath() {
        return path;
    }
}
