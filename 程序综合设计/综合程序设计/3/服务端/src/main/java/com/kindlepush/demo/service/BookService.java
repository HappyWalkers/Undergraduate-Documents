package com.kindlepush.demo.service;

import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.kindlepush.demo.mapper.BookMapper;
import com.kindlepush.demo.pojo.Book;
import org.springframework.stereotype.Service;

@Service
public class BookService extends ServiceImpl<BookMapper,Book> {


}
