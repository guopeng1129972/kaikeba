let Vue;
// 1.实现插件
class VueRouter {
  // 插件需要实现一个install方法
  constructor(options) {
    Vue;
    this.options = options;
    // 数据响应式，current必须是响应式的，这样他变化，使用他的组件就会重新render
    // 如何创造一个响应式数据
    // 1.借鸡生蛋 - new Vue({data:{current:'/'}})
    // 2.使用Vue.util.defineReactive(obj,'current','/'); 
    // this.current = window.location.hash.slice(1) || "/";
    Vue.util.defineReactive(this, "current", window.location.hash.slice(1));
    // 监控url变化
    window.addEventListener("hashchange", () => {
      this.current = window.location.hash.slice(1);
    });
  }
}
VueRouter.install = function (_Vue) {
  Vue = _Vue;
  // 注册router实例
  // 通过全局混入：Vue.mixin({beforeCreate})
  Vue.mixin({
    beforeCreate() {
      // 仅在根组件创建时执行一次
      if (this.$options.router) {
        Vue.prototype.$router = this.$options.router;
      }
    },
  });
  // 注册router-view和router-link组件
  Vue.component("router-view", {
    render(h) {
      //  url=>component url获取方式 1.window.location.hash 2.router:this.$router
      const { current, options } = this.$router;
      console.log(current, options);
      let component = null;
      Array.from(options.routes).forEach((index) => {
        if (index.path == current) {
          component = index.component;
        }
      });
      return h(component);
    },
  });
  Vue.component("router-link", {
    props: {
      to: {
        type: String,
        required: true,
      },
    },
    // jsx写render
    render(h) {
      h;
      // return h("a", "router-link");
      // <router-link to='/xxx'>xxx</router-link>
      // <a href='#/about'>xxx</a>
      // return <a href={`#${this.to}`}>{this.$slots.default}</a>;
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
};

export default VueRouter;
