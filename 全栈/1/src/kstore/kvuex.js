// 实现一个插件
// 实现store
let Vue;
class Store {
  constructor(options) {
    // 响应式处理的数据
    // this.state = new Vue({
    //   data: options.state,
    // });
    // setInterval(() => {
    //   this.state.counter++;
    // }, 1000);
    // state;
    this._vm = new Vue({
      data: {
        // 添加2个$vue就不会代理
        $$state: options.state,
      },
    });
    this._mutations = options.mutations;
    this._actions = options.actions;
    this.commit = this.commit.bind(this);
    this.dispatch = this.dispatch.bind(this);
  }
  get state() {
    return this._vm._data.$$state;
  }
  set state(v) {
    console.error("请使用replaceState重置状态");
  }
  // 修改状态 commit('add',payload)
  commit(type, payload) {
    const mutation = this._mutations[type];
    if (!mutation) {
      console.error("mutation不存在");
      return;
    } else {
      mutation(this.state, payload);
    }
  }
  dispatch(type, payload) {
    const action = this._actions[type];
    if (!action) {
      console.error("mutation不存在");
      return;
    } else {
      action(this, payload);
    }
  }
}
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
export default { Store, install };
