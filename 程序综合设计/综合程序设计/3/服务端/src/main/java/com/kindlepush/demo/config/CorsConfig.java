package com.kindlepush.demo.config;


import com.kindlepush.demo.interceptor.CookieInt;
import org.springframework.context.annotation.Configuration;
import org.springframework.web.servlet.config.annotation.CorsRegistry;
import org.springframework.web.servlet.config.annotation.InterceptorRegistry;
import org.springframework.web.servlet.config.annotation.WebMvcConfigurationSupport;
import org.springframework.web.servlet.config.annotation.WebMvcConfigurer;

import java.io.IOException;

@Configuration
public class CorsConfig implements WebMvcConfigurer {

    @Override
    public void addCorsMappings(CorsRegistry registry) {
        registry.addMapping("/**")
                .allowedOrigins("http://www.bmq.com")
                .allowCredentials(true)
                .allowedMethods("GET", "POST", "DELETE", "PUT","OPTIONS")
                .maxAge(3600);
    }

//    @Override
//    public void addInterceptors(InterceptorRegistry registry)
//    {
//        //注册自己的拦截器并设置拦截的请求路径
//        try {
//            registry.addInterceptor(new CookieInt()).addPathPatterns("/**");
//        } catch (IOException e) {
//            e.printStackTrace();
//        }
//        WebMvcConfigurer.super.addInterceptors(registry);
//    }


}
