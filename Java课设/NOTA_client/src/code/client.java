package code;

import javax.swing.*;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import javax.swing.table.DefaultTableCellRenderer;

import java.awt.*;
import java.awt.event.*;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileWriter;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.ObjectInputStream;
import java.io.OutputStream;
import java.io.PrintStream;
import java.net.Socket;
import java.util.Vector;
import java.awt.Font;

public class client {

    public class ancestor extends JFrame {
        protected JPanel jPanel = new JPanel();
        protected Socket s = null;
        protected OutputStream os = null;
        protected PrintStream ps = null;
        protected InputStream is = null;
        protected BufferedReader br = null;
        protected String title = null;

        public ancestor(String str) {
            super(str);
            title = str;

            this.setVisible(true);
            this.setLocationRelativeTo(null);
            this.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
            this.setResizable(false);

            try {
                s = new Socket(ConstVarible.address_home_wifi, ConstVarible.port);
                os = s.getOutputStream();
                ps = new PrintStream(os);
                is = s.getInputStream();
                br = new BufferedReader(new InputStreamReader(is));
            } catch (Exception ex) {
                ex.printStackTrace();
            }
        }
    }

    public class login extends ancestor implements ActionListener, FocusListener {// 登录界面
        private GridLayout gridLayout = new GridLayout(3, 2, 20, 20);
        private JLabel label_name = new JLabel("账号");
        private JLabel label_password = new JLabel("密码");
        private JTextField input_name = new JTextField("输入账号");
        private JPasswordField input_password = new JPasswordField("输入密码");
        private JButton registerButton = new JButton("去注册");
        private JButton loginButton = new JButton("登录");

        public login() {
            super("登录界面");
            jPanel.setLayout(gridLayout);
            jPanel.add(label_name);
            jPanel.add(input_name);
            jPanel.add(label_password);
            jPanel.add(input_password);
            jPanel.add(loginButton);
            jPanel.add(registerButton);
            this.add(jPanel);

            this.setSize(400, 300);
            this.setLocationRelativeTo(null);

            registerButton.addActionListener(this);
            loginButton.addActionListener(this);
            input_name.addFocusListener(this);
            input_password.addFocusListener(this);
            input_password.addActionListener(this);
        }

        public void actionPerformed(ActionEvent e) {
            JButton jButton = new JButton("jButton");
            try {
                jButton = (JButton) e.getSource();
            } catch (Exception ex) {
                log();
                return;
            }

            if (jButton.getText().compareTo("去注册") == 0) {
                new client().new register();
                this.dispose();
            } else {
                log();
            }
        }

        public void log() {
            String realPassword = null;
            try {
                ps.println("login");
                ps.println(input_name.getText());
                // System.out.println("waiting");
                realPassword = br.readLine();
                // System.out.println("waiting2");
            } catch (Exception ex) {
                ex.printStackTrace();
            } finally {
                try{
                    br.close();
                }catch(Exception ex){
                    ex.printStackTrace();
                }
            }
            if (realPassword.compareTo(String.valueOf(input_password.getPassword())) == 0) {
                JOptionPane.showMessageDialog(null, "登录成功");
                new client().new mainInterface(input_name.getText());
                this.dispose();
            } else {
                JOptionPane.showMessageDialog(null, "账号不存在或密码错误");
                new client().new login();
                this.dispose();
            }
        }

        public void focusGained(FocusEvent fe) {
            if (input_name.isFocusOwner() == true) {
                input_name.setText("");
            }
            if (input_password.isFocusOwner() == true) {
                input_password.setText("");
            }

        }

        public void focusLost(FocusEvent fe) {
            if (input_name.isFocusOwner() == false) {
                // input_name.setText("输入账号");
            }
            if (input_password.isFocusOwner() == false) {
                // input_password.setText("输入密码");
            }

        }
    }

    public class register extends ancestor implements ActionListener, FocusListener {
        private GridLayout gridLayout = new GridLayout(4, 2, 20, 20);
        private JLabel label_name = new JLabel("账号");
        private JLabel label_password = new JLabel("密码");
        private JLabel label_password_again = new JLabel("确认密码");
        private JTextField input_name = new JTextField("输入账号");
        private JPasswordField input_password = new JPasswordField("输入密码");
        private JPasswordField input_password_again = new JPasswordField("重复密码");
        private JButton registerButton = new JButton("注册");
        private JButton cancelButton = new JButton("取消");

        public register() {
            super("注册界面");
            input_name.addFocusListener(this);
            input_password.addFocusListener(this);
            input_password_again.addFocusListener(this);
            jPanel.setLayout(gridLayout);
            jPanel.add(label_name);
            jPanel.add(input_name);
            jPanel.add(label_password);
            jPanel.add(input_password);
            jPanel.add(label_password_again);
            jPanel.add(input_password_again);
            jPanel.add(registerButton);
            jPanel.add(cancelButton);
            this.add(jPanel);
            this.setSize(500, 400);
            this.setLocationRelativeTo(null);

            registerButton.addActionListener(this);
            cancelButton.addActionListener(this);
        }

        public void actionPerformed(ActionEvent e) {
            JButton jButton = (JButton) e.getSource();
            if (jButton.getText().compareTo("注册") == 0) {
                if (String.valueOf(input_password.getPassword())
                        .compareTo(String.valueOf(input_password_again.getPassword())) == 0) {
                    try {
                        os = s.getOutputStream();
                        ps = new PrintStream(os);
                        ps.println("register");
                        ps.println(input_name.getText());
                        ps.println(String.valueOf(input_password.getPassword()));

                        is = s.getInputStream();
                        br = new BufferedReader(new InputStreamReader(is));
                        if (br.readLine().compareTo("success") == 0) {
                            JOptionPane.showMessageDialog(this, "注册成功");
                            new client().new mainInterface(input_name.getText());
                            this.dispose();
                        } else {
                            JOptionPane.showMessageDialog(this, "此账号已存在");
                            new client().new register();
                            this.dispose();
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
                } else {
                    JOptionPane.showMessageDialog(null, "密码与确认密码不一致，请重新输入");
                }

            } else if (jButton.getText().compareTo("取消") == 0) {
                new client().new login();
                this.dispose();
            }
        }

        public void focusGained(FocusEvent fe) {
            if (input_name.isFocusOwner() == true) {
                input_name.setText("");
            }
            if (input_password.isFocusOwner() == true) {
                input_password.setText("");
            }
            if (input_password_again.isFocusOwner() == true) {
                input_password_again.setText("");
            }
        }

        public void focusLost(FocusEvent fe) {
        }
    }

    public class mainInterface extends ancestor implements ActionListener {
        protected JMenuBar jMenuBar = new JMenuBar();
        protected JMenu file = new JMenu("文件");
        protected JMenuItem newNote = new JMenuItem("新建笔记");
        protected JMenuItem saveNote = new JMenuItem("保存笔记");
        protected JMenuItem openNote = new JMenuItem("打开笔记");
        protected JMenuItem deleteNote = new JMenuItem("删除笔记");
        protected JMenuItem inquireNote = new JMenuItem("查询笔记");
        protected JMenuItem downloadNote = new JMenuItem("下载笔记");
        protected JMenu friends = new JMenu("好友");
        protected JMenuItem makefriends = new JMenuItem("添加好友");
        protected JMenuItem myfriends = new JMenuItem("我的好友");
        protected JMenuItem shareNote = new JMenuItem("分享笔记");
        protected JMenuItem getSharedNote = new JMenuItem("获得笔记");
        protected JMenu accountJMenu=new JMenu("我的");
        protected JMenuItem modifiyInfo=new JMenuItem("修改账户信息");
        protected JMenuItem exitItem=new JMenuItem("退出");
        protected JTextArea newJTextArea = new JTextArea(30, 60);
        protected JScrollPane newJScrollPane = new JScrollPane(newJTextArea);
        protected String title=null;

        public mainInterface(String str) {
            super(str + "的笔记");
            title=str;
            newNote.addActionListener(this);
            saveNote.addActionListener(this);
            openNote.addActionListener(this);
            deleteNote.addActionListener(this);
            inquireNote.addActionListener(this);
            downloadNote.addActionListener(this);
            makefriends.addActionListener(this);
            myfriends.addActionListener(this);
            shareNote.addActionListener(this);
            getSharedNote.addActionListener(this);
            modifiyInfo.addActionListener(this);
            exitItem.addActionListener(this);
            jPanel.add(jMenuBar);
            jMenuBar.add(file);
            jMenuBar.add(friends);
            jMenuBar.add(accountJMenu);
            file.add(newNote);
            file.add(saveNote);
            file.add(openNote);
            file.add(deleteNote);
            file.add(inquireNote);
            file.add(downloadNote);
            friends.add(makefriends);
            friends.add(myfriends);
            friends.add(shareNote);
            friends.add(getSharedNote);
            accountJMenu.add(modifiyInfo);
            accountJMenu.add(exitItem);

            jPanel.setLayout(null);
            this.add(jPanel);
            this.setSize(1000, 700);
            jMenuBar.setBounds(430, 20, 120, 30);
            this.setLocationRelativeTo(null);
        }

        public void actionPerformed(ActionEvent ae) {
            JMenuItem jMenuItem = (JMenuItem) ae.getSource();
            if (jMenuItem.getText().compareTo("新建笔记") == 0) {
                new newNote(title);
            } else if (jMenuItem.getText().compareTo("保存笔记") == 0) {
                new saveNote(title, this);
            } else if (jMenuItem.getText().compareTo("打开笔记") == 0) {
                new openNote(title);
            } else if (jMenuItem.getText().compareTo("删除笔记") == 0) {
                new deleteNote(title);
            } else if (jMenuItem.getText().compareTo("查询笔记") == 0) {
                new inquireNote(title);
            } else if (jMenuItem.getText().compareTo("下载笔记") == 0) {
                new downloadNote(title);
            }else if(jMenuItem.getText().compareTo("退出")==0){
                ps.println("exit");
                ps.println(title);
                System.exit(0);
            }
        }
    }

    public class newNote extends mainInterface {
        public newNote(String str) {
            super(str);
            this.setTitle(str + "的新建笔记");
            jPanel.add(newJScrollPane);
            this.add(jPanel);

            newJScrollPane.setBounds(90, 80, 800, 520);
            Font jTextAreaFont = new Font("楷体_GB2312", Font.PLAIN, 15);
            newJTextArea.setFont(jTextAreaFont);
            // newJTextArea.setLineWrap(true);
        }
    }

    public class saveNote extends ancestor implements ActionListener {
        private JLabel nameJLabel = new JLabel("笔记名称");
        private JTextField nameJTextField = new JTextField();
        private JButton saveButton = new JButton("保存");
        private JButton cancelButton = new JButton("取消");
        private GridLayout gridLayout = new GridLayout(2, 2, 20, 20);
        mainInterface anotherInterface = null;

        public saveNote(String str, mainInterface jframe) {
            super(str);
            anotherInterface = jframe;
            this.setTitle(str + "的保存笔记");
            this.setVisible(true);
            this.setSize(300, 170);
            jPanel.setLayout(gridLayout);
            this.setLocationRelativeTo(null);

            jPanel.add(nameJLabel);
            jPanel.add(nameJTextField);
            jPanel.add(saveButton);
            jPanel.add(cancelButton);
            this.add(jPanel);

            saveButton.addActionListener(this);
            cancelButton.addActionListener(this);
        }

        public void actionPerformed(ActionEvent ae) {
            JButton jButton = (JButton) ae.getSource();
            if (jButton.getText().compareTo("保存") == 0) {
                String account = anotherInterface.title;
                ps.println("save");
                ps.println(account + "_" + nameJTextField.getText() + ".txt");// 用户名+name
                String str = "str";
                try {
                    str = br.readLine();
                } catch (Exception ex) {
                    ex.printStackTrace();
                }
                if (str.compareTo("exist") == 0) {
                    int isCover = JOptionPane.showConfirmDialog(this, "该笔记本名称已存在，继续保存将覆盖原有笔记本，是否继续？");
                    if (isCover == 0) {// 确认覆盖,接着执行后面的程序
                        ps.println("yes");
                    } else {// 否则，重新输入
                        ps.println("no");
                        return;
                    }
                }

                ps.println(anotherInterface.newJTextArea.getText());
                ps.println(ConstVarible.endFlag);
                try {
                    String str1 = br.readLine();
                    if (str1.compareTo("success") == 0) {
                        JOptionPane.showMessageDialog(this, "保存成功");
                    }
                } catch (Exception ex) {
                    ex.printStackTrace();
                }
                this.dispose();

            } else if (jButton.getText().compareTo("取消") == 0) {
                this.dispose();
            }
        }
    }

    public class openNote extends mainInterface implements ListSelectionListener {
        protected JTable jTable = null;
        protected JScrollPane jScrollPane = null;
        private Vector<Vector<String>> data = new Vector<>();
        private Vector<String> columnName = new Vector<>();

        public openNote(String str) {
            super(str);
            this.setTitle(str + "的打开笔记");

            ps.println("open");
            ps.println(str);
            String notename = null;
            try {
                while (true) {
                    notename = br.readLine();
                    if (notename.compareTo(ConstVarible.endFlag) == 0) {
                        break;
                    }
                    notename = notename.substring(notename.lastIndexOf("\\") + 1);
                    notename = notename.substring(notename.indexOf("_") + 1, notename.indexOf("."));
                    Vector<String> row = new Vector<>();
                    row.add(notename);
                    data.add(row);
                }
            } catch (Exception ex) {
                ex.printStackTrace();
            }

            FlowLayout flowLayout = new FlowLayout();
            jPanel.setLayout(flowLayout);

            columnName.add("笔记名称");
            jTable = new JTable(data, columnName);
            jTable.setPreferredScrollableViewportSize(new Dimension(900, 500));
            Font font = new Font(ConstVarible.font_String,ConstVarible.font_style,ConstVarible.font_size);
            jTable.setFont(font);
            jTable.getSelectionModel().addListSelectionListener(this);
            jTable.setFillsViewportHeight(true);
            jScrollPane = new JScrollPane(jTable);
            jPanel.add(jScrollPane);
            this.add(jPanel);

        }

        public void valueChanged(ListSelectionEvent le) {
            int row = jTable.getSelectedRow();
            if (le.getValueIsAdjusting() == false) {
                ps.println(row);
                newNote opennote = new newNote(title);
                opennote.setTitle(title + "的笔记：" + jTable.getModel().getValueAt(row, 0));
                this.dispose();
                try {
                    while (true) {
                        String string = br.readLine();
                        if (string.compareTo(ConstVarible.endFlag) == 0) {
                            break;
                        }
                        opennote.newJTextArea.append(string + "\n");
                    }
                } catch (Exception ex) {
                    ex.printStackTrace();
                }

            }
        }
    }

    public class deleteNote extends openNote {
        public deleteNote(String str) {
            super(str);
            this.setTitle(str + "的删除笔记");
        }

        public void valueChanged(ListSelectionEvent le) {
            int row = jTable.getSelectedRow();
            if (le.getValueIsAdjusting() == false) {
                ps.println(row);
                newNote opennote = new newNote(title);
                opennote.setTitle(title + "的笔记：" + jTable.getModel().getValueAt(row, 0));
                try {
                    while (true) {
                        String string = br.readLine();
                        if (string.compareTo(ConstVarible.endFlag) == 0) {
                            break;
                        }
                        opennote.newJTextArea.append(string + "\n");
                    }
                } catch (Exception ex) {
                    ex.printStackTrace();
                }
                int isDeleted = JOptionPane.showConfirmDialog(opennote, "是否删除该笔记？");
                if (isDeleted == 0) {
                    ps.println("delete");
                    ps.println(row);
                    try {
                        if (br.readLine().compareTo("success") == 0) {
                            opennote.newJTextArea.setText("");
                            opennote.dispose();
                            this.dispose();
                            JOptionPane.showMessageDialog(this, "删除成功");
                        } else {
                            JOptionPane.showMessageDialog(this, "删除失败");
                        }
                    } catch (Exception ex) {
                        ex.printStackTrace();
                    }

                }
            }
        }
    }

    public class inquireNote extends mainInterface{
        protected JTable jTable = null;
        protected JScrollPane jScrollPane = null;
        public inquireNote(String str) {
            super(str);
            this.setTitle(str + "的查询笔记");
            this.dispose();
            String keyWord=JOptionPane.showInputDialog(this, "请输入您想要查询的关键词");
            if(keyWord==null){
                return;
            }
            if(keyWord.compareTo("")==0){
                JOptionPane.showMessageDialog(this, "未输入任何内容");
                return;
            }
            this.setVisible(true);

            ps.println("inquire");
            ps.println(title);
            ps.println(keyWord);

            Vector<Vector<String>> data=null;
            ObjectInputStream objectInputStream=null;
            try{
                objectInputStream=new ObjectInputStream(is);
                data=(Vector<Vector<String>>)objectInputStream.readObject();
            }catch(Exception ex){
                System.out.println("objecetInputStream");
                ex.printStackTrace();
            }
                
            FlowLayout flowLayout = new FlowLayout();
            jPanel.setLayout(flowLayout);

            Vector<String> columnName=new Vector<>();
            columnName.add("笔记名称");
            columnName.add("出现次数");
            for(int i=1;i<=5;i++){
                columnName.add("第"+i+"行次出现在(行,列)");
            }

            jTable = new JTable(data, columnName);
            jTable.setPreferredScrollableViewportSize(new Dimension(900, 500));
            Font font = new Font("楷体_GB2312", Font.PLAIN, 15);
            jTable.setFont(font);
            DefaultTableCellRenderer defaultTableCellRenderer=new DefaultTableCellRenderer();
            defaultTableCellRenderer.setHorizontalAlignment(JLabel.CENTER);
            jTable.setDefaultRenderer(Object.class, defaultTableCellRenderer);
            jTable.setFillsViewportHeight(true);
            jScrollPane = new JScrollPane(jTable);
            jPanel.add(jScrollPane);
            this.add(jPanel);
            this.validate();
        }

    }

    public class downloadNote extends openNote {
        int row = jTable.getSelectedRow();
        JFileChooser jFileChooser = null;
        File noteDownload = null;
        FileWriter fileWriter = null;

        public downloadNote(String str) {
            super(str);
            this.setTitle(str + "的下载笔记");
        }

        public void valueChanged(ListSelectionEvent le) {
            int row = jTable.getSelectedRow();
            if (le.getValueIsAdjusting() == false) {
                jFileChooser = new JFileChooser();
                jFileChooser.setDialogTitle("选择下载路径");
                jFileChooser.setApproveButtonText("选择");
                jFileChooser.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
                int returnVal = jFileChooser.showOpenDialog(this);
                String noteDownloadPath = null;
                if (returnVal == JFileChooser.APPROVE_OPTION) {
                    noteDownloadPath = jFileChooser.getSelectedFile().getAbsolutePath();
                }
                String notename = JOptionPane.showInputDialog(this, "请输入笔记名称");
                noteDownload = new File(noteDownloadPath + "\\" + notename + ConstVarible.format_txt);
                try {
                    fileWriter = new FileWriter(noteDownload);
                } catch (Exception ex) {
                    ex.printStackTrace();
                }

                ps.println(row);
                try {
                    while (true) {
                        String string = br.readLine();
                        if (string.compareTo(ConstVarible.endFlag) == 0) {
                            break;
                        }
                        fileWriter.write(string + "\n");
                    }
                } catch (Exception ex) {
                    ex.printStackTrace();
                    JOptionPane.showMessageDialog(this, "下载失败");
                    return;
                }
                finally{
                    try{
                        fileWriter.close();
                    }catch(Exception ex){
                        ex.printStackTrace();
                    }
                    
                }
                JOptionPane.showMessageDialog(this, "下载成功");
                this.dispose();
            }
        }
    }

    public static void main(String[] args) {
        client c = new client();
        login l = c.new login();
    }
}