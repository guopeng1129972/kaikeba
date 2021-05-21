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
- 使用jsx的写法也可以，但是会有问题，依赖当前的渲染环境有处理jsx的能力
```js
return <a href={`#${this.to}`}>{this.$slots.default}</a>;
```
- 这里渲染为什么不使用template的写法，是因为没有compiler编译
- render(h)，如果给h穿参数为一个组件，就会直接渲染这个组件
```js
render(h){  
  return h(components);
}
```