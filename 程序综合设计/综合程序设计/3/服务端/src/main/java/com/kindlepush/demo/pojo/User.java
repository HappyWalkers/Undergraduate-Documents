package com.kindlepush.demo.pojo;


import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;

@TableName("userinfo")
public class User{

    @TableId(type= IdType.AUTO)
    private Long userid;
    private String username;
    private String userpwd;
    private String email;


    private String kindleemail;

    @Override
    public String toString() {
        return "User{" +
                "userid=" + userid +
                ", username='" + username + '\'' +
                ", userpwd='" + userpwd + '\'' +
                ", email='" + email + '\'' +
                ", kindle_email='" + kindleemail + '\'' +
                '}';
    }

    public String getKindleemail() {
        return kindleemail;
    }

    public void setKindleemail(String kindle_email) {
        this.kindleemail = kindle_email;
    }

    public User(Long userid, String username, String userpwd, String email, String kindle_email) {
        this.userid = userid;
        this.username = username;
        this.userpwd = userpwd;
        this.email = email;
        this.kindleemail = kindle_email;
    }

    public User() {
    }

    public User(Long userid, String username, String userpwd, String email) {
        this.userid = userid;
        this.username = username;
        this.userpwd = userpwd;
        this.email = email;

    }

    public Long getUserid() {
        return userid;
    }

    public void setUserid(Long userid) {
        this.userid = userid;
    }


    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }


    public String getUserpwd() {
        return userpwd;
    }

    public void setUserpwd(String userpwd) {
        this.userpwd = userpwd;
    }


    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

}
