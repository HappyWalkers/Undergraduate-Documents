package code;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileReader;
import java.io.PrintStream;
import java.util.ArrayList;
import java.util.Properties;
import java.util.Set;
import java.util.TreeMap;
import java.util.Vector;

import javax.swing.JOptionPane;

public class fileOperation {
    private static Properties pps;
    static {
        pps = new Properties();
        FileReader reader = null;
        try {
            File file=new File(ConstVarible.dataPath + "account.inc");
            if(file.exists()==false){
                file.createNewFile();
            }
            reader = new FileReader(file);
            pps.load(reader);
        } catch (Exception ex) {
            JOptionPane.showMessageDialog(null, "文件操作异常1");
            System.exit(0);
        } finally {
            try {
                reader.close();
            } catch (Exception ex) {
                ex.printStackTrace();
            }
        }
    }

    public static void register(String nickname, String password) {
        pps.setProperty(nickname, password);
        PrintStream ps = null;
        try {
            ps = new PrintStream(ConstVarible.dataPath + "account.inc");
            pps.list(ps);
        } catch (Exception ex) {
            JOptionPane.showMessageDialog(null, "文件操作异常2");
            System.exit(0);
        } finally {
            try {
                ps.close();
            } catch (Exception ex) {
                ex.printStackTrace();
            }
        }
    }

    public static String getPasswordByAccount(String account) {
        String password = pps.getProperty(account);
        return password;
    }

    public static boolean check(String str) {// 没找到返回false，找到返回true
        if (pps.getProperty(str) == null) {
            return false;
        } else {
            return true;
        }
    }

    public static boolean checkNoteName(String str) {// filename已存在返回true，否则false
        File file = new File(ConstVarible.dataPath + str);
        // System.out.println(ConstVarible.dataPath + str);
        if (file.exists() == true) {
            return true;
        } else {
            return false;
        }
    }

    public static ArrayList<String> getFileNameByAccount(String account) {
        File file = new File(ConstVarible.dataFile);
        File[] files = file.listFiles();
        ArrayList<String> arrayList = new ArrayList<String>();
        for (File f : files) {
            String filename = f.getAbsolutePath();
            // System.out.println(filename);
            if (filename.startsWith(ConstVarible.dataPath+account + "_")) {
                arrayList.add(filename);
            }
        }
        return arrayList;
    }

    public static int countWordInFile(String word,File file)throws Exception{
        FileInputStream fis=new FileInputStream(file);
        byte[] data=new byte[(int)file.length()];
        fis.read(data);
        fis.close();
        String msg=new String(data);
        String aft=msg.replace(word, "");
        return (msg.length()-aft.length())/word.length();
    }

    public static Vector<Vector<String>> getClientInfo(){
        File file=new File(ConstVarible.dataFile);
        File[] files=file.listFiles();
        Vector<Vector<String>> data=new Vector<>();
        TreeMap<String,Integer> treeMap=new TreeMap<>();
        for(File f:files){
            String filename=f.getName();
            String str=filename.replace("_", "");
            int numOf_=(filename.length()-str.length())/"_".length();
            if(numOf_==1){
                if(treeMap.containsKey(filename)){
                    treeMap.put(filename.substring(0,filename.indexOf("_")),treeMap.get(filename)+1);
                }
                else{
                    treeMap.put(filename.substring(0,filename.indexOf("_")),1);
                }
            }
        }
        Set keySet=treeMap.keySet();
        for(Object key:keySet){
            Vector<String> row=new Vector<>();
            // System.out.println(key+" "+treeMap.get(key));
            row.add(String.valueOf(key));
            row.add(String.valueOf(treeMap.get(key)));
            data.add(row);
        }
        return data;
    }
}