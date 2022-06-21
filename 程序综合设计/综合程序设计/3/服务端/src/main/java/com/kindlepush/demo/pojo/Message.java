package com.kindlepush.demo.pojo;

public class Message{
    int statusCode;
    String info;

    public Message(int statusCode, String info) {
        this.statusCode = statusCode;
        this.info = info;
    }

    @Override
    public String toString() {
        return "Message{" +
                "statusCode=" + statusCode +
                ", info='" + info + '\'' +
                '}';
    }

    public int getStatusCode() {
        return statusCode;
    }

    public void setStatusCode(int statusCode) {
        this.statusCode = statusCode;
    }

    public String getInfo() {
        return info;
    }

    public void setInfo(String info) {
        this.info = info;
    }
}
