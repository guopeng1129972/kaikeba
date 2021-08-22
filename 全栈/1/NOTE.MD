# 1.Router 这个插件需要做什么事情？

# 2.为什么要在配置中加入 router 的配置项

# 3.router-view 为什么要放在根组件中？为什么一定要放？

# 4.跳转是如何实现内容刷新，但是页面不刷新？spa 的实现策略是啥样的？

# 实现 vue-router

spa 页面不能刷新（不能更改 url 的 host）,那么就有两种方案，

- 1.hash 监控
- 2.history api

url 发生变化显示对应的内容：
1.router-view:占位容器 2.数据响应式（router-view 的内容是根据 url 的变换进行动态变化的，要想实现数据驱动，而不去进行 dom 操作，就必须实现数据响应式，即利用 vue 的响应式，实现 router-view 的内容切换）

- 1.首先要实现一个插件,为什么？ vue.use(xxx) xxx 就是一个插件
- 插件需要实现一个 install 方法，而这个方法会在 use 方法中调用，并把当前的构造函数传进去
- 还有这个插件需要实现 router-view 和 router-link 的默认组件中
- src/krouter/kvue-router.js

```js
Vue.component("router-link", {
  props: {
    to: {
      type: String,
      required: true,
    },
  },
  render(h) {
    // <a href='#/about'>xxx</a>
    return h(
      "a",
      {
        attrs: {
          href: `#${this.to}`,
        },
      },
      this.$slots.default
    );
  },
});
```

- 使用 jsx 的写法也可以，但是会有问题，依赖当前的渲染环境有处理 jsx 的能力

```js
return <a href={`#${this.to}`}>{this.$slots.default}</a>;
```

- 这里渲染为什么不使用 template 的写法，是因为没有 compiler 编译
- render(h)，如果给 h 穿参数为一个组件，就会直接渲染这个组件

```js
render(h){
  return h(components);
}
```

- 实现 router-view,就是将 router-link 过来的组件，渲染到 router-view 上去
  注册 router 实例
  通过全局混入：Vue.mixin({beforeCreate})

```js
Vue.mixin({
  beforeCreate() {
    // 仅在根组件创建时执行一次 含义：在组件创建之前，就是new Vue()执行的时候
    // 获取传入的options,绑定到prototype上去，将router,也可以理解为一个闭包
    if (this.$options.router) {
      Vue.prototype.$router = this.$options.router;
    }
  },
});
```

- 但是这样的话也不能够触发响应式更新，因为虽然 this.current 发生了改变，但是它并不是响应式数据，
  说白了，就是底层没设置 defineProperty 的 get set，可以用 vue.util.defineReactive(obj,'current')
  添加响应式的属性
- 创建响应式数据

```js
class VueRouter {
  constructor(options) {
    // 数据响应式，current必须是响应式的，这样他变化，使用他的组件就会重新render
    // 如何创造一个响应式数据
    // 1.借鸡生蛋 - new Vue({data:{current:'/'}})
    // 2.使用Vue.util.defineReactive(obj,'current','/');
    // this.current = window.location.hash.slice(1) || "/";
    //含义：给当前this(当前VueRouter实例)添加响应式属性 current 初始值为window.location.hash.slice(1)
    Vue.util.defineReactive(this, "current", window.location.hash.slice(1));
  }
}
```

- 为啥么使用 vue.set()不行？因为 vue.set(obj,'key','value'),的 obj 首先得是响应式对象，当前情况不行
  因为 VueRouter 不是响应式对象

# 实现 vuex

## src/kstore/kvuex.js

## src/kstore/index.js

- 同理创建 Store 类
- 实现 install 方法，mixin beforeCreate 的时候注册$store

```js
function install(_vue) {
  Vue = _vue;
  // 注册$store
  Vue.mixin({
    beforeCreate() {
      if (this.$options.store) {
        Vue.prototype.$store = this.$options.store;
      }
    },
  });
}
```

- 处理响应式数据

```js
// 响应式处理的数据
this.state = new Vue({
  data: options.state,
});
setInterval(() => {
  this.state.counter++;
}, 1000);
```
- 这样是可以，但是暴露了Vue实例，不利于使用
  因为使用框架的人可以随时修改Vue实例上的方法，可能会带来其他的bug
  这样显得过于简单
- 所以要使用封装的去实现

- 实现getter
- 实现深层的vue-router
