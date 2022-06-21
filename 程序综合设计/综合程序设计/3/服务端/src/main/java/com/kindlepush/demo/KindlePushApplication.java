package com.kindlepush.demo;

import org.mybatis.spring.annotation.MapperScan;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.CrossOrigin;

@CrossOrigin(origins = {"http://localhost:8088", "null"})
@SpringBootApplication
@MapperScan("com.kindlepush.demo.mapper")
public class KindlePushApplication {

    public static void main(String[] args) {
        SpringApplication.run(KindlePushApplication.class, args);
    }

}
