#ifndef _NET_OPERATOR_CODE_H_
#define _NET_OPERATOR_CODE_H_

enum operatorcode{
	QUICK_LOGIN = 1000, //快速登录
	THIRID_LOGIN = 10001, //第三方登陆
	BD_BIND_PUSH = 1100, //百度推送绑定

	//推荐
	FIND_STORE_APP = 2100,// 应用商城推荐
	FIND_STORE_BOOK = 2101, //书城推荐
	FIND_STORE_GAME = 2102,//游戏商城推荐
	FIND_STORE_MAIN = 2103,//首页推荐

	//商城
	SUMMARY_INFOS = 3100, // 应用详情
	APP_WANT_URL = 3101, //获取下载地址
	APP_WANT_LIKE = 3102, //点赞

	//书城
	BOOK_TOPICS = 4100,//专题活动
	BOOK_SEARCH = 4101,//类别搜索
	BOOK_WANT = 4102//获取此书
};


#endif
