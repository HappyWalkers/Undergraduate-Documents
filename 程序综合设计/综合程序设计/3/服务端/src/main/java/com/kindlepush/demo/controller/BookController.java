package com.kindlepush.demo.controller;

import com.baomidou.mybatisplus.core.toolkit.Wrappers;
import com.kindlepush.demo.pojo.Book;
import com.kindlepush.demo.pojo.Message;
import com.kindlepush.demo.pojo.User;
import com.kindlepush.demo.service.BookService;
import com.kindlepush.demo.service.UserService;
import com.kindlepush.demo.utils.MailUtils;
import com.kindlepush.demo.utils.RedisUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.http.converter.feed.RssChannelHttpMessageConverter;
import org.springframework.stereotype.Controller;

import org.springframework.util.ObjectUtils;
import org.springframework.web.bind.annotation.*;
import redis.clients.jedis.Jedis;

import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

@Controller
@RequestMapping("/api/book")
public class BookController {

    @Autowired
    private BookService bookService;

    @Autowired
    private UserService userService;

    @Autowired
    public MailUtils mailUtils;

    public Jedis jedis = RedisUtils.initPool().getResource();

    public BookController() throws IOException {
    }

    //无参数时，返回默认排序数据
    @PostMapping("/search")
    public ResponseEntity<List<Book>> search(@RequestBody(required = false) Map<String,String> searchby, HttpServletResponse response){
        //初始化 如果未传参数 则默认随机排序
        List<Book> books=bookService.list();

        //获取数据,前台无参数POST时，searchby是null，所以必须校验
        if(searchby==null){
            searchby = new HashMap<>();
        }
        String bookname = searchby.get("bookname");
        String author = searchby.get("author");
        String username = searchby.get("username")==null?"":searchby.get("username");

        //有书名没作者
        if(bookname!=null&&author==null) {
            System.out.println(searchby);
            books = bookService.list(Wrappers.<Book>query().like("bookname", searchby.get("bookname")));
        }
        //有作者没书名
        if(bookname==null&&author!=null) {
            System.out.println(searchby);
            books = bookService.list(Wrappers.<Book>query().like("author",searchby.get("author")));
        }
        //有作者也有书名
        if(searchby.get("bookname")!=null&&searchby.get("author")!=null) {
            System.out.println(searchby);
             books = bookService.list(Wrappers.<Book>query().like("bookname", searchby.get("bookname"))
             .like("author",searchby.get("author")));
        }
        //清除路径信息
        books.forEach(x->x.setPath(""));


//        response.addCookie(new Cookie("token",jedis.get(username)));

        System.out.println(jedis.get(username));

        return ResponseEntity.ok(books);
    }


    //点进详情页面时 展示书籍具体信息
    @PostMapping("/item")
    public ResponseEntity<Book> findById(@RequestBody Map<String,Integer> idMap){
        Integer bookid = idMap.get("bookid");
        System.out.println(1);
        Book book = bookService.getOne(Wrappers.<Book>query().eq("bookid", bookid));
        System.out.println(book);
        return ResponseEntity.ok(book);
    }

    @PostMapping("/send")
    public ResponseEntity<Message> sendBook(@RequestBody Map<String,Integer> info, @CookieValue(name = "token",required = false,defaultValue = "")String token){
//        System.out.println(info.get("bookid"));
        Book resultBook = bookService.getById(info.get("bookid"));
        String path = resultBook.getPath();
        String username =  jedis.get(token);
        String kindleemail;

        System.out.println(token);

        if(username==null){
            return ResponseEntity.status(400).body(
                    new Message(400,"登录已过期，请重新登录！")
            );
        }else{
            //用户已经登录 并且得到了用户名  日后可在此处写扣费逻辑
            User user = userService.getOne(Wrappers.<User>query().eq("username", username));
            kindleemail = user.getKindleemail();
        }


        Boolean sendFileSuccess = mailUtils.sendMailWithAttachment(path, kindleemail);
        if(sendFileSuccess){
            return ResponseEntity.status(200).body(
                    new Message(200,"发送成功，请查收您的Kindle个人资料库！")
            );
        }else{
            return ResponseEntity.status(400).body(
                    new Message(400,"发送失败，请稍后重试！")
            );
        }

    }


}
