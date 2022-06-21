package com.kindlepush.demo.controller;

import com.baomidou.mybatisplus.core.toolkit.Wrappers;
import com.kindlepush.demo.pojo.Message;
import com.kindlepush.demo.pojo.User;
import com.kindlepush.demo.service.UserService;
import com.kindlepush.demo.utils.MailUtils;
import com.kindlepush.demo.utils.RedisUtils;
import com.kindlepush.demo.utils.TokenUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;
import redis.clients.jedis.Jedis;
import redis.clients.jedis.params.SetParams;

import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.Map;
import java.util.Objects;

@Controller
@RequestMapping("/api/user")
public class UserController {

    @Autowired
    public UserService userService;

    @Autowired
    public MailUtils mailUtils;

    public Jedis jedis = RedisUtils.initPool().getResource();

    public UserController() throws IOException {
    }




    @PostMapping("/login")
    @ResponseBody
    public  ResponseEntity<Message> login(@RequestBody User user, HttpServletResponse response){


        User dbUser = userService.getOne(Wrappers.<User>query().eq("username", user.getUsername()));

        if(dbUser==null){
            return ResponseEntity.status(404).body(
                    new Message(404,"用户名不存在！")
            );
        }
//        System.out.println(dbUser.getUserpwd()+","+user.getUserpwd());
//        ==和equals区别
//        System.out.println(dbUser.getUserpwd().equals(user.getUserpwd()));

        if(dbUser.getUserpwd().equals(user.getUserpwd())){

            
            //保存临时token
            //设置超时时间
            SetParams setParams = new SetParams();
            setParams.ex(7200);
//
            String token = TokenUtils.generate(24);
            jedis.set(user.getUsername(), token,setParams);
//            //也将value作为key，便于通过token反查用户名
//            String token = jedis.get(user.getUsername()+"_temp");
//            System.out.println(token);
            jedis.set(token,user.getUsername(),setParams);
//
//
            Cookie cookie = new Cookie("token",token);
            cookie.setMaxAge(7200);
            cookie.setDomain("www.leyou.com");
            cookie.setPath("/");


            Cookie cookie1 = new Cookie("SameSite","None");
            cookie1.setDomain("www.leyou.com");
            cookie1.setPath("/");
//            cookie1.setSecure(true);

            response.addCookie(cookie);
            response.addCookie(cookie1);

            return ResponseEntity.status(200).body(
                  new Message(200,"登录成功！")
            );
        }
        return ResponseEntity.status(400).body(
                new Message(400,"密码错误，请重新输入！")
        );
    }

    @PostMapping("/checklogin")
    @ResponseBody
    public  ResponseEntity<Message> checklogin(@CookieValue(value = "token",required = false,defaultValue = " ")String token){

        if(jedis.get(token)!=null){
            return ResponseEntity.ok().build();
        }else{
            return ResponseEntity.status(400).build();
        }
    }


    @PostMapping("/email")//@RequestBody User user,
    public ResponseEntity<Message> setEmail(@RequestBody Map<String,String> info,@CookieValue(name = "token",required = false,defaultValue = "")String token){
        
//        String redisToken = jedis.get(user.getUsername());
        String username = jedis.get(token);
        User user = userService.getOne(Wrappers.<User>query().eq("username",username));

        if(user==null||info.get("email")==null){
            return ResponseEntity.badRequest().body(
                    new Message(400,"请输入要更改的新注册邮箱地址！")
            );
        }

        //验证通过 设置邮箱
//        if(redisToken.equals(token)){
            user.setEmail(info.get("email"));
            boolean success = userService.updateById(user);
            if(success){
                return ResponseEntity.ok().body(
                        new Message(200,"注册邮箱设置成功！")
                );
            }else{
                return ResponseEntity.status(500).body(
                        new Message(500,"注册邮箱设置失败，请稍后重试。")
                );
            }
//        }else{
//            return ResponseEntity.badRequest().body(
//                    new Message(400,"token有误，请重新登录！")
//            );
//        }
    }

    @PostMapping("logout")
    public ResponseEntity<Message> logout(HttpServletResponse response,@CookieValue(name = "token",required = false,defaultValue = "")String token){
        String username = jedis.get(token);
        jedis.del(username);
        jedis.del(token);

        return ResponseEntity.ok().build();
    }

    @PostMapping("/passwd")
    public ResponseEntity<Message> setPasswd(@RequestBody Map<String,String> info, @CookieValue(name = "token",required = false,defaultValue = "")String token){
        String username =info.get("username");
//        String redisToken = jedis.get(info.get("username"));
        String oldPasswd = info.get("oldpasswd");
        String newPasswd = info.get("newpasswd");

        if(oldPasswd==null||newPasswd==null){
            return ResponseEntity.badRequest().body(
                    new Message(400,"请输入完整的旧密码和新密码！")
            );
        }

//        //验证token通过
//        if(redisToken.equals(token)){

            User trueUser = userService.getOne(Wrappers.<User>query().eq("username",username));
            String trueOldPasswd =trueUser.getUserpwd();
            if(!oldPasswd.equals(trueOldPasswd)){
                return ResponseEntity.badRequest().body(
                        new Message(400,"旧密码有误！")
                );
            }else{
                trueUser.setUserpwd(newPasswd);
                boolean success=false;
                try {
                     success = userService.updateById(trueUser);
                }catch(Exception e){
                    e.printStackTrace();
                }
                if(success){
                    return ResponseEntity.ok().body(
                            new Message(200,"新密码设置成功！")
                    );
                }else{
                    return ResponseEntity.status(500).body(
                            new Message(500,"新密码设置失败，请稍后重试。")
                    );
                }
            }

//        }else{
//            return ResponseEntity.badRequest().body(
//                    new Message(400,"token有误，请重新登录！")
//            );
//        }

    }


    @PostMapping("/getCapcha")
    public ResponseEntity<Message> getCapcha(@RequestBody Map<String,String> info,@CookieValue(name = "token",required = false,defaultValue = "")String token){
        String username = info.get("username");
        String redisToken = jedis.get(username);
        String email = info.get("email");
        if(email==null){
            return ResponseEntity.badRequest().body(
                    new Message(400,"请输入接收验证码的邮箱！")
            );
        }

//        不需要token
//        if(!info.get("token").equals(token)){
//            return ResponseEntity.badRequest().body(
//                    new Message(400,"token有误，请重新登录！")
//            );
//        }

        String subject = "来自KindlePush的验证码,五分钟内有效";
        String capcha = TokenUtils.generate(6);
        Boolean sendSuccess = mailUtils.sendMail(subject, capcha, email);
        if(sendSuccess){
            //存入redis
            SetParams params = new SetParams();
            params.ex(600);
            jedis.set(username+"_capcha",capcha,params);


            return ResponseEntity.ok().body(
                    new Message(200,"发送成功！")
            );
        }else{
            return ResponseEntity.status(500).body(
                    new Message(500,"发送失败，请稍后重试。")
            );
        }

    }

    @PostMapping("/register")
    public ResponseEntity<Message> register(@RequestBody Map<String,String> info){
        String username;
        String userpwd;
        String email;
        String capcha;
        String kindle_email;


        try {
            //info里要有 username userpwd email capcha
            username = Objects.requireNonNull(info.get("username"));
            userpwd = Objects.requireNonNull(info.get("userpwd"));
            email = Objects.requireNonNull(info.get("email"));
            capcha = Objects.requireNonNull(info.get("capcha"));
            kindle_email = Objects.requireNonNull(info.get("kindleemail"));

        }catch(NullPointerException e){
            return ResponseEntity.badRequest().body(
                    new Message(400,"输入信息有误，请重新登录！"));
        }
        //验证码通过
        if(jedis.get(username+"_capcha").equals(capcha)){
            boolean save = userService.save(
                    new User(null, username, userpwd, email,kindle_email)
            );
            if(save){

                //使验证码失效
                jedis.del(username+"_capcha");

                return ResponseEntity.ok().body(
                        new Message(200,"注册成功！")
                );
            }else{
                return ResponseEntity.status(500).body(
                        new Message(500,"注册失败，请稍后重试。")
                );
            }
        }else{
            return ResponseEntity.status(500).body(
                    new Message(500,"验证码有误！")
            );
        }

    }

}
