package com.kindlepush.demo.utils;


import redis.clients.jedis.JedisPool;

import java.io.IOException;
import java.io.InputStream;
import java.util.Properties;

public class RedisUtils {


    public  static JedisPool initPool() throws IOException {
        InputStream inputStream = RedisUtils.class.getResourceAsStream("/redis-config.properties");
        Properties properties = new Properties();
        properties.load(inputStream);
//        System.out.println(properties);

        String[] address = properties.getProperty("ip").split(":");
        JedisPool pool = new JedisPool(address[0]);

        return pool;

    }



}
