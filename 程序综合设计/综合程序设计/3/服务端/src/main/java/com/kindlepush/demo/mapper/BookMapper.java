package com.kindlepush.demo.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.kindlepush.demo.pojo.Book;
import org.springframework.stereotype.Repository;

@Repository
public interface BookMapper extends BaseMapper<Book> {

}
