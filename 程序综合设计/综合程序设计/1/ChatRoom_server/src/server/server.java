package server;
import java.awt.event.*;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.BorderLayout;
import java.awt.Font;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.ObjectOutputStream;
import java.io.PrintStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.SocketException;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.LinkedHashSet;
import java.util.Vector;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import javax.swing.table.DefaultTableCellRenderer;
public class server {
    public LinkedHashSet<String> linkedHashSet = new LinkedHashSet<>();// 全局变量
    public String accountString = new String();
    public ArrayList clients = new ArrayList<>();//存放所有连接用户
    public void sendMessage(String msg) {//向公用窗口发送信息
        for (int i = 0; i < clients.size(); i++) {
            singleClient sc = (singleClient) clients.get(i);
            if (sc.ID.compareTo("public") == 0) {
                sc.ps.println(msg);
            }
        }
    }
    public void sendMessageToSomeone(String account, String message) {//向account发送私聊消息
        for (int i = 0; i < clients.size(); i++) {
            singleClient sc = (singleClient) clients.get(i);
            if (sc.account.compareTo(account) == 0 && sc.ID.compareTo("private") == 0) {
                sc.ps.println(message);
            }
        }
    }
    public class ancestor extends JFrame {//祖先窗口，进行基本窗口设置
        protected JPanel jPanel = new JPanel();
        protected ServerSocket ss = null;
        protected Socket s = null;
        protected String title = null;
        public ancestor(String title) {
            super(title);
            this.title = title;
            this.setVisible(true);
            this.setLocationRelativeTo(null);
            this.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        }
    }
    public class mainInterface extends ancestor implements ActionListener, Runnable {//主界面窗口
        private JButton sendButton = new JButton("系统消息");
        private JButton force = new JButton("管理当前连接的用户");
        public mainInterface() {
            super("服务器");
            jPanel.add(sendButton);
            jPanel.add(force);
            this.add(jPanel);
            this.setSize(400, 250);
            jPanel.setLayout(null);
            sendButton.setBounds(135, 30, 100, 50);
            force.setBounds(90, 120, 200, 60);
            this.setLocationRelativeTo(null);
            this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            sendButton.addActionListener(this);
            force.addActionListener(this);
            try {
                ss = new ServerSocket(ConstVarible.port);
                new Thread(this).start();//多线程开启
            } catch (Exception ex) {
                ex.printStackTrace();
            }
        }
        public void run() {
            try {
                while (true) {//多线程不断接受用户连接请求
                    s = ss.accept();
                    singleClient sc = new singleClient(s);
                    new Thread(sc).start();
                    clients.add(sc);//将连接用户存入clients
                }
            } catch (Exception ex) {
                ex.printStackTrace();
            }
        }
        public void actionPerformed(ActionEvent ae) {
            JButton jButton = (JButton) ae.getSource();
            if (jButton.getText().compareTo("系统消息") == 0) {
                new message(s);
            } else if (jButton.getText().compareTo("管理当前连接的用户") == 0) {
                new force();
            }
        }
    }
    public class singleClient implements Runnable {//为每个用户开启的收消息线程
        private Socket s = null;
        private BufferedReader br = null;
        public PrintStream ps = null;
        public String account = "account";
        protected String ID = "public";
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
                ID = br.readLine();//先读入ID和account
                account=br.readLine();
                while (true) {
                    String str = new String();
                    try {
                        str = br.readLine();
                    } catch (SocketException ex) {
                        if (ex.getMessage().compareTo("Connection reset") == 0) {
                            linkedHashSet.remove(accountString);// 断开连接抛出java.net.SocketException:
                                                                // Connectionreset，移除该用户连接
                            sendMessage("系统消息：" + accountString + "下线");
                            break;
                        }
                    }
                    if ((ConstVarible.startFlag + "login").compareTo(str) == 0) {//登录
                        // account = br.readLine();
                        accountString = account;
                        String password = fileOperation.getPasswordByAccount(account);
                        // System.out.println(password);
                        ps.println(password);
                        linkedHashSet.add(account);
                        sendMessage("系统消息：" + account + "上线");
                    }
                    if ((ConstVarible.startFlag + "register").compareTo(str) == 0) {//注册
                        // account = br.readLine();
                        accountString = account;
                        String password = br.readLine();
                        if (fileOperation.check(account) == false) {
                            fileOperation.register(account, password);
                            ps.println("success");
                        } else {
                            ps.println("failed");
                        }
                        linkedHashSet.add(account);
                        sendMessage("系统消息：" + account + "上线");
                    }
                    if ((ConstVarible.startFlag + "send").compareTo(str) == 0) {//发送消息
                        try {
                            while (true) {
                                String string = br.readLine();
                                sendMessage(string);
                                br.readLine();// 读掉一个ID
                                br.readLine();//读掉account
                                br.readLine();// 读掉起始符
                            }
                        } catch (Exception ex) {
                            ex.printStackTrace();
                        }
                    }
                    if ((ConstVarible.startFlag + "makefriends").compareTo(str) == 0) {//添加好友
                        // account = br.readLine();
                        String friendAccount = br.readLine();
                        int res = fileOperation.storeFriendsAccount(account, friendAccount);
                        // System.out.println("hh");
                        if (res == 0) {
                            ps.println("该好友账户不存在");
                        } else if (res == 1) {
                            ps.println("您已经添加过该好友");
                        } else if (res == 2) {
                            ps.println("添加成功");
                        } else if (res == 3) {
                            ps.println("添加失败");
                        }
                    }
                    if ((ConstVarible.startFlag + "list").compareTo(str) == 0) {//查看好友列表
                        // account = br.readLine();
                        ObjectOutputStream objectOutputStream = new ObjectOutputStream(s.getOutputStream());
                        objectOutputStream.writeObject(fileOperation.getfriend(account));
                    }
                    if ((ConstVarible.startFlag + "chat").compareTo(str) == 0) {//查看在线好友
                        // account = br.readLine();
                        Vector<Vector<String>> friends = fileOperation.getfriend(account);
                        for (int i = 0; i < friends.size(); i++) {
                            String string = friends.get(i).get(0);
                            Iterator<String> iterator = linkedHashSet.iterator();
                            while (iterator.hasNext()) {
                                if (string.compareTo(iterator.next()) == 0) {
                                    ps.println(string);
                                    // System.out.println(string);
                                }
                            }
                        }
                        ps.println(ConstVarible.endFlag);
                    }
                    if ((ConstVarible.startFlag + "chatprivate").compareTo(str) == 0) {//私聊
                        // account = br.readLine();
                        String friendAccount = br.readLine();// 好友账户
                        // for (int i = 0; i < clients.size(); i++) {// 给好友发送通知
                        // if (friendAccount.compareTo(((singleClient) clients.get(i)).account) == 0) {
                        // ((singleClient) clients.get(i)).ps.println(ConstVarible.startFlag +
                        // "chatprivate");
                        // ((singleClient) clients.get(i)).ps.println(account);
                        // // System.out.println(((singleClient) clients.get(i)).account);
                        // System.out.println(i);
                        // }
                        // }
                        sendMessage("系统消息："+account+"向"+friendAccount+"发起私聊");
                        try {
                            while (true) {
                                String string = br.readLine();
                                if (string == null)
                                    break;
                                sendMessageToSomeone(friendAccount, string);
                                sendMessageToSomeone(account, string);
                                // br.readLine();// 读掉起始符
                            }
                        } catch (Exception ex) {
                            ex.printStackTrace();
                        }
                    }
                }
            } catch (Exception ex) {
                ex.printStackTrace();
            } finally {
                try {
                    br.close();
                } catch (Exception ex) {
                    ex.printStackTrace();
                }
            }
        }
    }
    public class message extends ancestor {//发送系统消息
        protected JTextArea taMsg = new JTextArea("以下是系统消息\n");
        protected JTextField tfMsg = new JTextField();
        protected JScrollPane newJScrollPane = new JScrollPane(taMsg);
        protected ActionListener sendListener = null;
        public message(Socket s) {
            super("系统消息");
            BorderLayout borderLayout = new BorderLayout();
            jPanel.setLayout(borderLayout);
            jPanel.add(newJScrollPane, BorderLayout.CENTER);
            jPanel.add(tfMsg, BorderLayout.SOUTH);
            Font font = new Font(ConstVarible.font_String, ConstVarible.font_style, ConstVarible.font_size);
            taMsg.setFont(font);
            tfMsg.setFont(font);
            taMsg.setEditable(false);
            tfMsg.setBackground(Color.yellow);
            sendListener = new ActionListener() {
                public void actionPerformed(ActionEvent ae) {
                    try {
                        sendMessage("系统消息：" + tfMsg.getText());
                        taMsg.append("系统消息：" + tfMsg.getText() + "\n");
                        tfMsg.setText("");
                    } catch (Exception ex) {
                        ex.printStackTrace();
                    }
                }
            };
            tfMsg.addActionListener(sendListener);
            this.add(jPanel);
            this.setSize(700, 500);
            this.setLocationRelativeTo(null);
            this.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        }
    }
    public class force extends ancestor implements ListSelectionListener {//强制某用户下线
        protected JTable jTable = null;
        protected JScrollPane jScrollPane = null;
        protected Vector<Vector<String>> data = new Vector<>();
        protected Vector<String> columnName = new Vector<>();
        public force() {
            super("强制下线当前连接的用户");
            columnName.add("当前在线用户");
            Iterator<String> iterator = linkedHashSet.iterator();
            while (iterator.hasNext()) {
                Vector<String> row = new Vector<>();
                row.add(iterator.next());
                data.add(row);
            }
            BorderLayout borderLayout = new BorderLayout();
            jPanel.setLayout(borderLayout);
            jTable = new JTable(data, columnName) {
                public boolean isCellEditable(int row, int column) {
                    return false;
                }
            };
            jTable.setPreferredScrollableViewportSize(new Dimension(600, 450));
            Font font = new Font(ConstVarible.font_String, ConstVarible.font_style, ConstVarible.font_size);
            jTable.setFont(font);
            jTable.setFillsViewportHeight(true);
            DefaultTableCellRenderer defaultTableCellRenderer = new DefaultTableCellRenderer();
            defaultTableCellRenderer.setHorizontalAlignment(JLabel.CENTER);
            jTable.setDefaultRenderer(Object.class, defaultTableCellRenderer);
            jTable.getSelectionModel().addListSelectionListener(this);
            jScrollPane = new JScrollPane(jTable);
            jPanel.add(jScrollPane, BorderLayout.CENTER);
            this.add(jPanel);
            this.setSize(700, 500);
            this.setLocationRelativeTo(null);
        }
        public void valueChanged(ListSelectionEvent le) {
            if (le.getValueIsAdjusting() == false) {
                int row = jTable.getSelectedRow();
                int option = JOptionPane.showConfirmDialog(this, "是否强制下线该用户？");
                if (option == JOptionPane.YES_OPTION) {
                    try {
                        for (int i = 0; i < clients.size(); i++) {
                            singleClient sc = (singleClient) clients.get(i);
                            if (sc.account.compareTo(data.get(row).get(0)) == 0) {
                                // System.out.println(i);
                                sc.ps.println(ConstVarible.startFlag + "exit");
                            }
                        }
                    } catch (Exception ex) {
                        ex.printStackTrace();
                    }
                }
            }
        }
    }
    public static void main(String[] args) {
        new server().new mainInterface();
    }
}