package com.kindlepush.demo;

import com.kindlepush.demo.utils.MailUtils;
import com.kindlepush.demo.utils.RedisUtils;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import redis.clients.jedis.Jedis;
import redis.clients.jedis.JedisPool;
import redis.clients.jedis.JedisPubSub;

import java.io.IOException;

@SpringBootTest
class KindlePushApplicationTests {


    @Test
    void jedisTests() throws IOException {
        JedisPool pool = new RedisUtils().initPool();

        Jedis jedis = pool.getResource();
        System.out.println(jedis.ping());

    }

    @Test
    void mailTests(){
        MailUtils mail = new MailUtils();
        System.out.println(mail.sendMail("hahahah", "test", "bmq123456@gmail.com"));
    }

}
