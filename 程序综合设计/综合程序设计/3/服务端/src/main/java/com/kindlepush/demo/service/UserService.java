package com.kindlepush.demo.service;

import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.kindlepush.demo.mapper.UserMapper;
import com.kindlepush.demo.pojo.User;
import org.springframework.stereotype.Service;

@Service
public class UserService extends ServiceImpl<UserMapper,User> {
}
