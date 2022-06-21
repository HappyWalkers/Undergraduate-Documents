package com.kindlepush.demo.utils;


import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.core.io.FileSystemResource;
import org.springframework.mail.SimpleMailMessage;
import org.springframework.mail.javamail.JavaMailSender;
import org.springframework.mail.javamail.JavaMailSenderImpl;
import org.springframework.mail.javamail.MimeMessageHelper;
import org.springframework.stereotype.Component;
import org.springframework.validation.annotation.Validated;

import javax.mail.MessagingException;
import javax.mail.internet.MimeMessage;
import javax.mail.internet.MimeUtility;
import java.io.UnsupportedEncodingException;

@Component
public class MailUtils {

//    @Autowired
    private JavaMailSenderImpl jms;

    public MailUtils() {
        jms = new JavaMailSenderImpl();
        jms.setHost("smtp.qq.com");
        jms.setProtocol("smtp");
        jms.setUsername("535834197@qq.com");
        jms.setPassword("qovjkvpolnexbgfd");
        jms.setDefaultEncoding("UTF-8");
    }

    public Boolean sendMailWithAttachment(String path, String receiver){

        MimeMessage message = jms.createMimeMessage();


        try {

            MimeMessageHelper helper = new MimeMessageHelper(message,true,"utf-8");
            helper.setFrom("535834197@qq.com");
            helper.setTo(receiver);
            helper.setSubject("书籍发送");
            helper.setText("这是您订阅的书籍");

            FileSystemResource file = new FileSystemResource(path);

            String filename = path.substring(path.lastIndexOf('\\')).substring(1);
            helper.addAttachment(MimeUtility.encodeWord(file.getFilename()),file);
            System.out.println(file.getFilename());

            jms.send(message);
            return Boolean.TRUE;//success

        } catch (MessagingException | UnsupportedEncodingException e) {
            e.printStackTrace();
            return Boolean.FALSE;//fail
        }

    }

    public Boolean sendMail(String subject,String text,String receiver){
        SimpleMailMessage message = new SimpleMailMessage();
        message.setFrom("535834197@qq.com");
        message.setTo(receiver);
        message.setSubject(subject);
        message.setText(text);

        try {
            jms.send(message);
            return Boolean.TRUE;
        }catch(Exception e){
            e.printStackTrace();
            return Boolean.FALSE;
        }
    }



}
