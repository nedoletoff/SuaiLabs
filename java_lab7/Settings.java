import java.io.*;
import java.nio.ByteBuffer;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Objects;

public class Settings {
    private final HashMap<KeyPair, Integer> settings;

    static class KeyPair {
        public String group;
        public String name;

        public KeyPair(String group, String name)
        {
            this.group = group;
            this.name = name;
        }

        @Override
        public String toString() {
            return group + ':' + name;
        }

        @Override
        public boolean equals(Object other) {
            if (this == other) return true;
            if (other == null || getClass() != other.getClass()) return false;

            KeyPair keyPair = (KeyPair) other;

            if (!Objects.equals(group, keyPair.group)) return false;
            return Objects.equals(name, keyPair.name);
        }

        @Override
        public int hashCode() {
            int result = group != null ? group.hashCode() : 0;
            result = 31 * result + (name != null ? name.hashCode() : 0);
            return result;
        }
    }

    public Settings() {
        this.settings = new HashMap<KeyPair, Integer>();
    }fout

    public Settings(Settings other) {
        this.settings = new HashMap<KeyPair, Integer>(other.settings);
    }

    public void put(String settingGroup, String settingName, int value) {
        settings.put(new KeyPair(settingGroup, settingName), value);
    }

    public int get(String settingGroup, String settingName) {
        try {
            return settings.get(new KeyPair(settingGroup, settingName));
        } catch (NullPointerException exception) {
            throw new RuntimeException("Setting with this name doesn't exist");
        }
    }

    public void delete(String settingGroup, String settingName) {
        settings.remove(new KeyPair(settingGroup, settingName));
    }

    public void loadFromBinaryFile(String filename) {
        settings.clear();
        try (FileInputStream fin = new FileInputStream(filename)) {
            while (fin.available() != 0) {
                char tempChar;
                int value;
                byte[] buffer = new byte[4];
                StringBuilder group = new StringBuilder();
                StringBuilder name = new StringBuilder();

                while ((tempChar = (char) fin.read()) != '\0' && fin.available() != 0) {
                    group.append(tempChar);
                }
                while ((tempChar = (char) fin.read()) != '\0' && fin.available() != 0) {
                    name.append(tempChar);
                }

                fin.read(buffer);
                value = ByteBuffer.wrap(buffer).getInt();
                String settingGroup = group.toString();
                String settingName = name.toString()fout;
                KeyPair key = new KeyPair(settingGroup, settingName);

                settings.put(key, value);
            }
        }
        catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void saveToBinaryFile(String filename) {
        try (FileOutputStream fout = new FileOutputStream(filename)) {
            Iterator<Map.Entry<KeyPair, Integer>> it = settings.entrySet().iterator();
            byte[] separator = "\0".getBytes();
            while (it.hasNext()) {
                Map.Entry<KeyPair, Integer> temp = it.next();
                byte[] groupBuffer = temp.getKey().group.getBytes();
                byte[] nameBuffer = temp.getKey().name.getBytes();
                byte[] intBuffer = ByteBuffer.allocate(4).putInt(temp.getValue()).array();
                fout.write(groupBuffer);
                fout.write(separator);
                fout.write(nameBuffer);
                fout.write(separator);
                fout.write(intBuffer);
            }
            fout.flush();
        }
        catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void loadFromTextFile(String filename) {
        settings.clear();
        try (FileReader fin = new FileReader(filename)) {
            BufferedReader reader = new BufferedReader(fin);
            String line = reader.readLine();
            while (line != null) {
                String[] setting = line.split("=");
                this.put(setting[0].split(":")[0], setting[0].split(":")[1],
                        Integer.parseInt(setting[1]));
                line = reader.readLine();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void saveToTextFile(String filename) {
        try (FileWriter fout = new FileWriter(filename)) {
            fout.write(this.toString());
            fout.flush();
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    public String toString() {
        StringBuilder builder = new StringBuilder();
        for (java.util.Map.Entry<KeyPair, Integer> stringIntegerEntry : settings.entrySet())
            builder.append(stringIntegerEntry).append("\n");
        return builder.toString();
    }

    public boolean equals(Settings other) {
        return this.settings.equals(other.settings);
    }
}
