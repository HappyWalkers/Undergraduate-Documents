import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;

import java.io.*;
import java.util.*;

public class Check {

    private Map<Object, Object> sensitiveWordsMap;
    private static final String END = "end";

    private void initMap(Set<String> words) {

        sensitiveWordsMap = new HashMap<>(words.size());
        String currentStr;
        Map<Object, Object> currentMap;
        Map<Object, Object> subMap;

        Iterator<String> iterator = words.iterator();

        while (iterator.hasNext()) {
            currentStr = iterator.next();
            currentMap = sensitiveWordsMap;

            for (int i = 0; i < currentStr.length(); i++) {
                char c = currentStr.charAt(i);
                subMap = (Map<Object, Object>) currentMap.get(c);
                if (subMap == null) {
                    subMap = new HashMap<>();
                    currentMap.put(c, subMap);
                    currentMap = subMap;
                } else {
                    currentMap = subMap;
                }
                if (i == currentStr.length() - 1) {
                    currentMap.put(END, "end");
                }

            }
        }

    }

    public Map<Set<Integer>, String> getSensitiveWords(String txt) {

        Map location = new HashMap<Set<Integer>, String>(); //Set里有两个元素，分别是初始位置和长度

        for (int i = 0; i < txt.length(); i++) {
            int sensitiveWordLength = getSensitiveWordLength(txt, i);
            if (sensitiveWordLength > 0) {
                Set key = new LinkedHashSet();
                key.add(i);
                key.add(sensitiveWordLength);

                String value = txt.substring(i, i + sensitiveWordLength);

                location.put(key, value);
                i = i + sensitiveWordLength - 1;
            }

        }

        return location;
    }

    private int getSensitiveWordLength(String txt, int i) {

        Map<Object, Object> currentMap = new HashMap<>();
        Map<Object, Object> subMap = new HashMap<>();
        currentMap = sensitiveWordsMap;

        int length = 0;
        boolean flag = false;
        char currentChar;

        while (true) {
            currentChar = txt.charAt(i);
            subMap = (Map<Object, Object>) currentMap.get(currentChar);

            if (subMap == null) {
                break;
            } else {
                length++;
                if (subMap.containsKey(END)) {
                    flag = true;
                }
                currentMap = subMap;
            }
            i++;
        }
        if (!flag) {
            length = 0;
        }
        return length;
    }

    public static void main(String[] args) throws IOException {

        //读取文件敏感词集
        Set<String> sensitiveWordsSet = new HashSet<>();
        File sensitiveWordsFile = new File("D://sensitiveWords.txt");
        FileReader sensitiveWordsFileReader = new FileReader(sensitiveWordsFile);
        BufferedReader sensitiveWordsBufferedReader = new BufferedReader(sensitiveWordsFileReader);
        String eachSensitiveWord;
        while((eachSensitiveWord=sensitiveWordsBufferedReader.readLine())!=null){
            sensitiveWordsSet.add(eachSensitiveWord);
        }

        //初始化敏感词集合
        Check textFilter = new Check();
        textFilter.initMap(sensitiveWordsSet);



        //TODO:用循环读取文件网址列表
        File urlsFile = new File("D://urls.txt");
        FileReader urlFileReader = new FileReader(urlsFile);
        BufferedReader urlBufferedReader = new BufferedReader(urlFileReader);
        String url,rawhtml;
        while((url=urlBufferedReader.readLine())!=null){
            System.out.println(url);
            rawhtml = Crawler.getHtml(url);
            //TODO:提取文本
            Document doc = Jsoup.parse(rawhtml);
            System.out.println(doc.text());
            System.out.println(textFilter.getSensitiveWords(rawhtml));
//            System.out.println(textFilter.getSensitiveWords(doc.text()));
        }












    }


}
