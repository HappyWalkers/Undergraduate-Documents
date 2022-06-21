package com.kindlepush.demo.interceptor;

import com.fasterxml.jackson.databind.ObjectMapper;
import com.kindlepush.demo.pojo.User;
import com.kindlepush.demo.utils.RedisUtils;
import com.kindlepush.demo.utils.TokenUtils;
import org.apache.commons.io.IOUtils;
import org.springframework.web.servlet.handler.HandlerInterceptorAdapter;
import redis.clients.jedis.Jedis;
import redis.clients.jedis.params.SetParams;

import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.nio.charset.Charset;

public class CookieInt extends HandlerInterceptorAdapter
{

    public Jedis jedis = RedisUtils.initPool().getResource();

    public CookieInt() throws IOException {
    }

    @Override
    public boolean preHandle(HttpServletRequest request, HttpServletResponse response, Object handler) throws Exception
    {
//        // 拦截处理代码
//        Cookie[] cookies = request.getCookies();
//        Cookie token=null;
//        if(cookies!=null){
//            for(Cookie cookie:cookies){
//                if(cookie.getName()=="token"){
//                    token = cookie;
//                }
//            }
//        }
//
//        String tokenStr = TokenUtils.generate(24);
//         if(token==null) {
//             token = new Cookie("token", tokenStr);
//             //如果是login
////             System.out.println(request.getMethod());
//
//         }
//         Boolean isLogin = request.getRequestURI().endsWith("login");
//         Boolean isPost = (request.getMethod().equals("POST"));
//        String s = request.getMethod();
////        if(isLogin&&isPost){
//////                 System.out.printf(request.getMethod());
//////                 System.out.println("hahah");
//////                 String jsonString = IOUtils.toString(request.getInputStream(), Charset.defaultCharset());
////            ObjectMapper mapper = new ObjectMapper();
////            User user = mapper.readValue(request.getInputStream(), User.class);
////
////            //这里将生成的token存到redis 然后在login函数中读取出来 如果密码正确就把token保存到redis
////            //设置超时时间
////            SetParams setParams = new SetParams();
////            setParams.ex(7200);
////            jedis.set(user.getUsername()+"_temp", tokenStr,setParams);
////
////        }
//
//         token.setPath("/");
//         token.setDomain("www.leyou.com");
//         token.setMaxAge(7200);
//
//
//         response.addCookie(token);
//        //返回true通过，返回false拦截
        return true;
    }
}