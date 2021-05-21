let Vue;
// 1.实现插件
class VueRouter {
  // 插件需要实现一个install方法
  constructor(options) {
    Vue;
    this.options=options
  }
}
VueRouter.install = function (_Vue) {
  Vue = _Vue;
  // 注册router-view和router-link组件
  Vue.component("router-view", {
    render(h) {
      //  url=>component
      return h(null);
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
