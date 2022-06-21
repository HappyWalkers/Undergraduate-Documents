import javax.print.DocFlavor;
import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.URL;

public class Crawler {

    public static String getHtml(String userurl){
        StringBuilder builder = new StringBuilder();
        String tmp;
        try {
            URL url = new URL(userurl);
            InputStream in = url.openStream();
            InputStreamReader reader = new InputStreamReader(in);
            BufferedReader bufferedReader = new BufferedReader(reader);

            while((tmp = bufferedReader.readLine())!=null){
                builder.append(tmp);
            }

        }catch(Exception e){
            e.printStackTrace();
        }
        return builder.toString();
    }


}
