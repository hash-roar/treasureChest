# vue
##  项目
技术栈: html5+css+es6+vue(vue,vuex,router,aoixs))+vuetify+php
+mysql+nginx+thinkphp

###已完成
1.数据库后台管理
![数据库管理.png](http://ww1.sinaimg.cn/large/007b6ma2ly1gswpuf2vikj31ya0zvkcj.jpg)
2登录页面
![Login.png](http://ww1.sinaimg.cn/large/007b6ma2ly1gswpyhga3kj30kv0y00u6.jpg)

## bugs

1. 在ajax异步请求数据中对data中变量进行赋值,值更新但是视图不更新,但是用箭头函数可以更新,猜想可能是箭头函数不生成this作用域的原因

## 剖析vue.js内部运行机制

[剖析vue.js内部运行机制](https://juejin.cn/book/6844733705089449991/section/6844733705211084808)

## vue项目结构
![vue项目结构.png](http://ww1.sinaimg.cn/large/007b6ma2ly1gstap8pfq5j30tb0qq7mw.jpg)

### vuex目录结构
![vuex目录结构.png](http://ww1.sinaimg.cn/large/007b6ma2ly1gstbqbq16mj31490jagqt.jpg)

#### vuex页面刷新丢失数据解决

	created() {
	    if (sessionStorage.getItem("store")) {
	      this.$store.replaceState(
	        Object.assign(
	          {},
	          this.$store.state,
	          JSON.parse(sessionStorage.getItem("store"))
	        )
	      );
	    }
	
	    //在页面刷新时将vuex里的信息保存到sessionStorage里
	    window.addEventListener("beforeunload", () => {
	      sessionStorage.setItem("store", JSON.stringify(this.$store.state));
	    });
	  },

### vue工程实践

[vue工程目录](https://learnku.com/articles/21099)