# Qt顶部弹出式消息框

#### 介绍
基于QDialog实现的顶部弹出式消息框

#### 使用说明

1. 在mainwindow函数新建`customMsg`对象

2. 调用`setBackgroundColor(QString)`设置背景颜色

3. 调用`setmsgType(messageType)`设置消息框类型
       

    

   | ENUM | CRITICAL                                                     | SUCCESS                                                      | WARNING                                                      | INFO                                                         |
   | ---- | ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ |
   | 图标 | <img src="../../../hexo/source/images/README/critical.png" style="zoom:50%;" /> | <img src="../../../hexo/source/images/README/success.png" alt="success" style="zoom:50%;" /> | <img src="../../../hexo/source/images/README/warning.png" alt="warning" style="zoom:50%;" /> | <img src="../../../hexo/source/images/README/info.png" alt="info" style="zoom:50%;" /> |

   

4. 调用`setContentText(QString)`设置消息框内容


#### 特技

1.  使用 Readme\_XXX.md 来支持不同的语言，例如 Readme\_en.md, Readme\_zh.md
2.  Gitee 官方博客 [blog.gitee.com](https://blog.gitee.com)
3.  你可以 [https://gitee.com/explore](https://gitee.com/explore) 这个地址来了解 Gitee 上的优秀开源项目
4.  [GVP](https://gitee.com/gvp) 全称是 Gitee 最有价值开源项目，是综合评定出的优秀开源项目
5.  Gitee 官方提供的使用手册 [https://gitee.com/help](https://gitee.com/help)
6.  Gitee 封面人物是一档用来展示 Gitee 会员风采的栏目 [https://gitee.com/gitee-stars/](https://gitee.com/gitee-stars/)
