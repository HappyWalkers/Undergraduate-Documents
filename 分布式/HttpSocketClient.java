import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.net.SocketAddress;

public class HttpSocketClient {

    private Socket mSocket;

    public static void main(String[] args) {
        HttpSocketClient client = new HttpSocketClient();
        try {
            client.sendGet("www.baidu.com",80,"/");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }


    public HttpSocketClient() {
        this.mSocket = new Socket();

    }

    /** 在百度服务器面前，这就是一个正常的浏览器
     * @param host
     * @param port
     * @param path
     * @throws IOException
     */
    void sendGet(String host, int port, String path) throws IOException {
        SocketAddress dest = new InetSocketAddress(host, port);
        mSocket.connect(dest);
        OutputStreamWriter streamWriter = new OutputStreamWriter(mSocket.getOutputStream());
        BufferedWriter bufferedWriter = new BufferedWriter(streamWriter);

        bufferedWriter.write("GET " + path + " HTTP/1.1\r\n");
        bufferedWriter.write("Host: " + host + "\r\n");
        bufferedWriter.write("Connection: " + "keep-alive" + "\r\n");
        bufferedWriter.write("User-Agent: " + "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/64.0.3282.140 Safari/537.36" + "\r\n");
        bufferedWriter.write("Accept: " + "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8" + "\r\n");
        bufferedWriter.write("Accept-Language: " + "zh-CN,zh;q=0.9,en-US;q=0.8,en;q=0.7" + "\r\n");
        bufferedWriter.write("\r\n");
        bufferedWriter.flush(); //flush一下很重要，等于说已经写完了


        BufferedInputStream stream = new BufferedInputStream(mSocket.getInputStream());
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(stream));
        String line = null;
        while ((line = bufferedReader.readLine())!=null) {
            System.out.println(line);
        }
        bufferedReader.close();
        bufferedWriter.close();
        mSocket.close();
    }
}