package code;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;

import java.awt.event.*;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.InputStreamReader;
import java.io.ObjectOutputStream;
import java.io.PrintStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Date;
import java.util.Iterator;
import java.util.LinkedHashSet;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Vector;
import java.awt.Font;
import java.awt.Dimension;

public class server {
    public LinkedHashSet<String> linkedHashSet = new LinkedHashSet<>();// 全局变量
    public String accountString =new String();
    public class ancestor extends JFrame {
        protected JPanel jPanel = new JPanel();
        protected ServerSocket ss = null;
        protected Socket s = null;
        protected String title = null;
        protected JTable jTable = null;
        protected JScrollPane jScrollPane = null;
        protected Vector<Vector<String>> data = new Vector<>();
        protected Vector<String> columnName = new Vector<>();

        public ancestor(String title) {
            super(title);
            this.title = title;
            this.setVisible(true);
            this.setLocationRelativeTo(null);
            // this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            this.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        }
    }

    public class mainInterface extends ancestor implements ActionListener, Runnable {
        private JButton all_users = new JButton("管理所有用户");
        private JButton now_users = new JButton("管理当前连接的用户");

        public mainInterface() {
            // GUI
            super("服务器");
            jPanel.add(all_users);
            jPanel.add(now_users);
            this.add(jPanel);

            this.setSize(400, 250);
            jPanel.setLayout(null);
            all_users.setBounds(115, 30, 150, 50);
            now_users.setBounds(90, 120, 200, 50);
            this.setLocationRelativeTo(null);
            this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

            all_users.addActionListener(this);
            now_users.addActionListener(this);

            // TCP
            try {
                ss = new ServerSocket(ConstVarible.port);
                new Thread(this).start();
            } catch (Exception ex) {
                ex.printStackTrace();
            }
        }

        public void run() {
            try {
                while (true) {
                    s = ss.accept();
                    singleClient sc = new singleClient(s);
                    new Thread(sc).start();
                }
            } catch (Exception ex) {
                ex.printStackTrace();
            }
        }

        public void actionPerformed(ActionEvent ae) {
            JButton jButton = (JButton) ae.getSource();
            if (jButton.getText().compareTo("管理所有用户") == 0) {
                new all_users();
            } else if (jButton.getText().compareTo("管理当前连接的用户") == 0) {
                new now_users();
            }
        }
    }

    public class singleClient implements Runnable {
        private Socket s = null;
        private BufferedReader br = null;// save,open,inquire,check account and password
        public PrintStream ps = null;// download,delete
        public String account = null;
        private ArrayList<String> arrayList = null;

        public singleClient(Socket s) {
            this.s = s;
            try {
                br = new BufferedReader(new InputStreamReader(s.getInputStream()));
                ps = new PrintStream(s.getOutputStream());
            } catch (Exception ex) {
                ex.printStackTrace();
            }

        }

        public void run() {

            try {
                while (true) {
                    String str = new String();
                    try {
                        str = br.readLine();
                    } catch (Exception ex) {
                        // ex.printStackTrace();
                        linkedHashSet.remove(accountString);// 断开连接抛出java.net.SocketException: Connectionreset，移除该用户连接
                        break;
                    }
                    if ("login".compareTo(str) == 0) {
                        account = br.readLine();
                        accountString=account;
                        String password = fileOperation.getPasswordByAccount(account);
                        ps.println(password);
                        linkedHashSet.add(account);
                    }
                    if ("register".compareTo(str) == 0) {
                        account = br.readLine();
                        accountString=account;
                        String password = br.readLine();
                        if (fileOperation.check(account) == false) {
                            fileOperation.register(account, password);
                            ps.println("success");
                        } else {
                            ps.println("failed");
                        }
                        linkedHashSet.add(account);
                    }
                    if ("save".compareTo(str) == 0) {
                        String filename = br.readLine();
                        if (fileOperation.checkNoteName(filename) == true) {
                            ps.println("exist");
                            String str1 = null;
                            try {
                                str1 = br.readLine();
                            } catch (Exception ex) {
                                ex.printStackTrace();
                            }
                            if (str1.compareTo("yes") == 0) {
                                ;// do nothing,接着执行后面的程序
                            } else {
                                new Thread(new singleClient(s)).start();
                                return;
                            }
                        } else {
                            ps.println("not exist");
                        }
                        File notebook = new File(ConstVarible.dataPath + filename);
                        FileWriter fileWriter = new FileWriter(notebook);
                        while (true) {
                            String string = br.readLine();
                            if (string.compareTo(ConstVarible.endFlag) == 0) {
                                break;
                            }
                            fileWriter.write(string + "\n");
                        }
                        fileWriter.close();
                        ps.println("success");
                    }
                    if ("open".compareTo(str) == 0) {
                        account = "str1";
                        arrayList = null;
                        try {
                            account = br.readLine();
                            arrayList = fileOperation.getFileNameByAccount(account);
                            for (int i = 0; i < arrayList.size(); i++) {
                                ps.println(arrayList.get(i));
                            }
                            ps.println(ConstVarible.endFlag);
                        } catch (Exception ex) {
                            ex.printStackTrace();
                        }
                        int noteSelected = Integer.parseInt(br.readLine());
                        String notename = arrayList.get(noteSelected);
                        File note = new File(notename);
                        FileReader fr = new FileReader(note);
                        BufferedReader br = new BufferedReader(fr);
                        while (true) {
                            String string = br.readLine();
                            if (string == null) {
                                break;
                            }
                            ps.println(string);
                        }
                        ps.println(ConstVarible.endFlag);
                        br.close();
                    }
                    if ("delete".compareTo(str) == 0) {
                        int noteDelete = Integer.parseInt(br.readLine());
                        File file = new File(arrayList.get(noteDelete));
                        String notename = arrayList.get(noteDelete);
                        notename = notename.substring(notename.lastIndexOf("\\") + 1);
                        notename = notename.substring(notename.indexOf("_") + 1, notename.indexOf("."));
                        Date date = new Date();
                        SimpleDateFormat simpleDateFormat = new SimpleDateFormat("yyyy_mm_dd_hh_mm_ss");
                        file.renameTo(new File(ConstVarible.dataPath + simpleDateFormat.format(date) + "_" + account
                                + "_" + notename + ConstVarible.format_txt));
                        if (fileOperation.checkNoteName(account + "_" + notename) == false) {
                            ps.println("success");
                        } else {
                            ps.println("failed");
                        }
                    }
                    if ("inquire".compareTo(str) == 0) {
                        String keyWord = null;
                        try {
                            account = br.readLine();
                            keyWord = br.readLine();
                        } catch (Exception ex) {
                            ex.printStackTrace();
                        }
                        arrayList = fileOperation.getFileNameByAccount(account);
                        File noteInquire = null;
                        Vector<Vector<String>> data = new Vector<>();
                        for (int i = 0; i < arrayList.size(); i++) {
                            noteInquire = new File(arrayList.get(i));
                            FileReader fileReader = new FileReader(noteInquire);
                            BufferedReader bufferedReader = new BufferedReader(fileReader);
                            String string = new String();
                            int row = 0;// 行数
                            Vector<String> noteVector = new Vector<>();
                            String notename = arrayList.get(i);
                            notename = notename.substring(notename.lastIndexOf("\\") + 1);
                            notename = notename.substring(0, notename.indexOf("."));
                            noteVector.add(notename);
                            try {
                                noteVector.add(String.valueOf(fileOperation.countWordInFile(keyWord, noteInquire)));
                                while (true) {
                                    row++;
                                    string = bufferedReader.readLine();
                                    if (string == null) {
                                        break;
                                    }
                                    int column = string.indexOf(keyWord);
                                    if (column != -1) {
                                        noteVector.add("(" + row + " , " + column + ")");
                                        if (noteVector.size() == 5) {
                                            break;
                                        }
                                    }
                                }
                                data.add(noteVector);
                            } catch (Exception ex) {
                                ex.printStackTrace();
                            } finally {
                                try {
                                    bufferedReader.close();
                                } catch (Exception ex) {
                                    ex.printStackTrace();
                                }
                            }
                        }
                        ObjectOutputStream objectOutputStream = new ObjectOutputStream(s.getOutputStream());
                        objectOutputStream.writeObject(data);
                    }
                    if ("exit".compareTo(str) == 0) {
                        String string = br.readLine();
                        linkedHashSet.remove(string);
                    }
                }
            } catch (Exception ex) {
                ex.printStackTrace();
            } finally {
                try {
                    br.close();
                } catch (Exception ex) {
                    // ex.printStackTrace();
                }
            }
        }
    }

    public class all_users extends ancestor {

        public all_users() {
            super("所有用户");

            columnName.add("用户名称");
            columnName.add("笔记数量");

            data = fileOperation.getClientInfo();
            jTable = new JTable(data, columnName);
            jTable.setPreferredScrollableViewportSize(new Dimension(900, 500));
            Font font = new Font(ConstVarible.font_String, ConstVarible.font_style, ConstVarible.font_size);
            jTable.setFont(font);
            jTable.setFillsViewportHeight(true);
            jScrollPane = new JScrollPane(jTable);
            jPanel.add(jScrollPane);
            this.add(jPanel);
            this.setSize(1000, 700);
            this.setLocationRelativeTo(null);
        }
    }

    public class now_users extends ancestor {

        public now_users() {
            super("当前连接的用户");
            columnName.add("用户名称");
            Iterator<String> iterator = linkedHashSet.iterator();
            while (iterator.hasNext()) {
                Vector<String> vector = new Vector<>();
                vector.add(iterator.next());
                data.add(vector);
            }
            jTable = new JTable(data, columnName);
            jTable.setPreferredScrollableViewportSize(new Dimension(900, 500));
            Font font = new Font(ConstVarible.font_String, ConstVarible.font_style, ConstVarible.font_size);
            jTable.setFont(font);
            jTable.setFillsViewportHeight(true);
            jScrollPane = new JScrollPane(jTable);
            jPanel.add(jScrollPane);
            this.add(jPanel);
            this.setSize(1000, 700);
            this.setLocationRelativeTo(null);
        }
    }

    public static void main(String[] args) {
        server s = new server();
        s.new mainInterface();
    }
}