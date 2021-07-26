# vue + vueRouter+vuex+axois+thinkphp5登录状态管理

### main.js
路由守卫对每一个路由判断是否需要登录

	router.beforeEach((to, from, next) => {
	  //判断是否需要登录
	  if (to.meta.requireAuth) {
	    //判断是否登录
	    if (store.getters.isLogin) {
	      next();
	    } else {
	      next({
	        path: '/login',
	        query: {
	          redirect: to.fullPath,
	        }
	      })
	    }
	  }else {
	    next();
	  }

###   route/index.js
路由表

	const routes = [
	  {
	    path: '/',
	    name: 'Home',
	    component: Home
	  },
	  {
	    path: '/about',
	    name: 'About',
	    // route level code-splitting
	    // this generates a separate chunk (about.[hash].js) for this route
	    // which is lazy-loaded when the route is visited.
	    component: () => import(/* webpackChunkName: "about" */ '../views/About.vue')
	  },
	  {
	    path: "/dbadmin",
	    name: "dataBaseAdmin",
	    meta:{
	      requireAuth:true
	    },
	    component: () => import("../views/DataBaseAdmin")
	  }, {
	    path:'/login',
	    name:"Login",
	    component:()=>import("../views/Login")
	  }
	]


### view/ login
用vuetify组件搭建登陆页面

	<template>
	  <div>
	    <v-card class="ma-auto px-5" flat>
	      <v-card-title>Login</v-card-title>
	
	      <v-card-text>
	        <v-form v-model="valid">
	          <v-container class="pa-0">
	            <v-row>
	              <v-col cols="12" md="4">
	                <v-text-field
	                  v-model="name"
	                  prepend-icon="mdi-account"
	                  :rules="nameRules"
	                  :counter="20"
	                  label="name"
	                  required
	                ></v-text-field>
	              </v-col>
	              <v-col cols="12" md="4">
	                <v-text-field
	                  v-model="password"
	                  prepend-icon="mdi-lock"
	                  :rules="nameRules"
	                  :counter="20"
	                  label="password"
	                  required
	                  :type="passShow ? 'text' : 'password'"
	                  :append-icon="passShow ? 'mdi-eye' : 'mdi-eye-off'"
	                  @click:append="passShow = !passShow"
	                ></v-text-field>
	              </v-col>
	            </v-row>
	          </v-container>
	          <v-card-actions class="mt-3"
	            ><v-spacer></v-spacer
	            ><v-btn @click="Login">Submit</v-btn></v-card-actions
	          >
	        </v-form>
	      </v-card-text>
	      <v-snackbar
	        timeout="2000"
	        absolute
	        bottom
	        :color="snackbar.color"
	        v-model="snackbar.bool"
	        text
	      >
	        {{ snackbar.message }}
	      </v-snackbar>
	    </v-card>
	  </div>
	</template>
	<script>
	export default {
	  data: () => ({
	    snackbar: {
	      bool: false,
	      message: "",
	      color: "red",
	    },
	    passShow: false,
	    valid: false,
	    name: "",
	    password: "",
	    nameRules: [
	      (v) => !!v || "Name is required",
	      (v) => v.length <= 20 || "Name must be less than 10 characters",
	    ],
	  }),
	  methods: {
	    Login() {
	      if (!this.valid) {
	        this.infom("complete the form !");
	        return;
	      }
	      let post = {
	        name: this.name,
	        password: this.password,
	      };
	      this.$axois
	        .post("/api/index/login", post)
	        .then((res) => {
	          let data = res.data;
	          console.log(data);
	          if (data.code == 404) {
	            this.infom("no such user");
	            return;
	          }
	          if (data.code == 403) {
	            this.infom("password wrong");
	            return;
	          }
	          this.infom("login success!", "blue");
	          this.$store.commit("setLogin");
	          this.$router.push(this.$route.query.redirect);
	        })
	        .catch(function (error) {
	          console.log(error);
	        });
	    },
	    infom(message, color = "red") {
	      this.snackbar.bool = true;
	      this.snackbar.message = message;
	      this.snackbar.color = color;
	    },
	  },
	};
	</script>	

### thinkphp   index/login/index 方法

	public function index()
    {
        $name = $this->request->param("name");
        $password = $this->request->param("password");
        $user = new UserMod();
        $result = [];
        $qury_res = $user->where("user_name", $name)->select();
        if (count($qury_res) == 0) {
            $result["code"] = 404;
            return json($result);
        }
        if ($password != $qury_res[0]["user_password"]) {
            $result["code"] = 403;
            return json($result);
        }
    }