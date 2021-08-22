# 第三节： vue2 源码剖析 01

## 搭建调试环境

- 获取地址：git clone https://github.com/vuejs/vue.git
- 安装依赖 npm install
- 安装 rollup: npm install --global rollup
- 修改 dev 脚本 ：添加 --sourcemap
- 执行 dev 脚本:npm run dev

## 调试技巧

- chrom 打开指定文件 command+p
- 断点

# 源码根目录

```bash
tree -L 1 -d
├── benchmarks
├── build/config 打包构建脚本
├── dist 发布目录
├── examples 范例，里面有测试代码
├── flow 针对flow的类型声明
├── node_modules
├── packages 核心代码之外的独立库
├── //script 构建脚本(最新版本集成到build里面)
├── src 源码
├── test
└── types  针对ts的类型声明
```

# 源码 src 目录

```bash
src
├── compiler 编译器相关
├── core 核心代码
│ ├── components 通用组件比如keep-alive
│ ├── global-api 全局API 静态方法 use() set()
│ ├── instance 构造函数等
│ ├── observer 响应式相关
│ ├── util 工具函数等 defineActive
│ └── vdom 虚拟dom相关
├── platforms
│  ├── web  浏览器平台
│  └── weex 移动端平台
├── server  服务端渲染相关
├── sfc 单文件组件相关
└── shared
```

- compiler 编译器 作用：将用户写的 template 编译成为 vdom

# 编译生成

- runtime:仅包含运行时，不包含编译时（不能写 template 选项）
- common:cjs 规范，用于 webpack1，用于服务端渲染
- esm:ES 模块，用于 webpack2+ 开发环境使用（平常用）
- umd:universal module definition 兼容 cjs 与 amd，用于浏览器(什么都不带)

# 查找 vue 编译以及运行时

- 通过 package.json 查找入口文件
  "dev": "rollup -w -c build/config.js --sourcemap --environment TARGET:web-full-dev"
  `--environment TARGET:web-full-dev` 为环境变量参数
- build/config.js 的 web-full-dev 就配置了入口文件

```js
  // Runtime+compiler development build (Browser)
  'web-full-dev': {
    entry: resolve('web/entry-runtime-with-compiler.js'),
    dest: resolve('dist/vue.js'),
    format: 'umd',
    env: 'development',
    alias: { he: './entity-decoder' },
    banner
  },
```

- 入口文件 `web/entry-runtime-with-compiler.js`,这都是 resolve 函数的参数，并不是绝对路径

```js
const resolve = (p) => {
  // p => web/xxx
  const base = p.split("/")[0];
  if (aliases[base]) {
    return path.resolve(aliases[base], p.slice(base.length + 1));
  } else {
    return path.resolve(__dirname, "../", p);
  }
};
```

- resolve 方法接收参数并 split("/")[0]，得到`web`,aliases[web],aliases 是一个集合，可以在它里面
  找到最终的路径，就找到入口文件了

# build/alias.js

```js
module.exports = {
  // ...
  core: resolve("src/core"),
  shared: resolve("src/shared"),
  web: resolve("src/platforms/web"),
  //...
};
```

## src/platforms/web/entry-runtime-with-compiler.js

- 得到入口文件
- 扩展$mount 方法，扩展的目的是添加处理 template 与 el 方法

```js
//扩展了$mount方法
const mount = Vue.prototype.$mount;
Vue.prototype.$mount = function (el?: string | Element, hydrating?: boolean) {
  //...
  // 又返回了当前的mount对象
  return mount.call(this, el, hydrating);
};
```

## src/platforms/web/runtime/index.js

- 1.实现了 patch 函数 patch 的用法
- patch 的两个用法
  1.vdom=>dom 初始化时，vdom 生成 dom 操作
  2.update vdom =>diff => dom operation(update del change)
  数据更新时，vdom diff 发生 dom 的 operation 时候触发
- 2.实现了$mount 实现挂载
- 但是到现在还没有找到运行时

## src/core/index.js

- 核心运行时，在这里初始化全局静态方法, 初始化全局 api:Vue.set/delete/use/component/...

```js
// 1.初始化全局api:Vue.set/delete/use/component/...
initGlobalAPI(Vue);
```

- 比如 use 方法 src/core/global-api/use.js

```js
// 1.比如 Vue.use(VueRouter,args,...)，截取VueRouter，把后面的转化为一个数组args
const args = toArray(arguments, 1);
// 2.组件在使用的时候，会传进来一个vue的构造函数_vue就是这里的this
//3.比如function install(Vue,arg1,arg2)
args.unshift(this);
if (typeof plugin.install === "function") {
  plugin.install.apply(plugin, args);
} else if (typeof plugin === "function") {
  plugin.apply(null, args);
}
```

## src/core/instance/index.js

```js
//2. 一下5个方法，均为实现Vue的实例方法和属性
initMixin(Vue);
stateMixin(Vue);
eventsMixin(Vue);
lifecycleMixin(Vue);
renderMixin(Vue);
```

## src/core/instance/init.js 以 initMixin()为例

```js
//1.合并选项
// user options + system options
if (options && options._isComponent) {
  // optimize internal component instantiatio
} else {
  // 2.可以通过this.$options访问
  vm.$options = mergeOptions(resolveConstructorOptions(vm.constructor));
}
// 3.初始化过程
vm._self = vm;
initLifecycle(vm); //4. 初始化属性 $children,$root,$par...
initEvents(vm); //5.自定义事件的监听 @click ...
initRender(vm); //6.插槽解析 _c和$createElement()<=>h的声明
callHook(vm, "beforeCreate");
// 7.初始化各种状态
initInjections(vm); // resolve injections before data/props
initState(vm); //8.props data methods watch
initProvide(vm); // resolve provide after data/props
callHook(vm, "created");
```

## src/core/instance/render.js

```js
// 1.插槽的解析
vm.$slots = resolveSlots(options._renderChildren, renderContext);
vm.$scopedSlots = emptyObject;
//2.render(h)中的 h就是$createElement 如果是编译器编译出来的结果，就是_c
vm._c = (a, b, c, d) => createElement(vm, a, b, c, d, false);
vm.$createElement = (a, b, c, d) => createElement(vm, a, b, c, d, true);
```

# Vue 的初始化过程？ new Vue()都做了什么？

执行\_init()方法；

- 组件实例初始化属性， initLifecycle 比如$children,$root,主要是按照 protp 声明当前的组件所在位置
- 整合 options 合并选项 user options + system options
- 处理自定义事件 initEvents @click
- 处理插槽信息 initRender
- 最重要的是组件状态初始化、响应式等事情 initInjections initState initProvide
- 两个生命周期的调用

```js
initMixin(Vue);

vm._self = vm;
initLifecycle(vm); //4. 初始化属性 $children,$root,$par...
initEvents(vm); //5.自定义事件的监听 @click ...
initRender(vm); //6.插槽解析 _c和$createElement()<=>h的声明
callHook(vm, "beforeCreate");
// 7.初始化各种状态
initInjections(vm); // resolve injections before data/props
initState(vm); //8.props data methods watch
initProvide(vm); // resolve provide after data/props
callHook(vm, "created");

stateMixin(Vue);
eventsMixin(Vue);
lifecycleMixin(Vue);
renderMixin(Vue);
```

- vue2 中一个组件对应一个 watcher 实例，称为渲染级 watcher
  在 watcher 中做依赖收集，调用一次 update
- src/core/instance/lifecycle.js

```js
    updateComponent = () => {
      // mycommit-2 组件更新函数，先执行组件render()
      vm._update(vm._render(), hydrating)
    }
  }
  //mycommit-1 在watcher中做依赖收集，执行一次190行
  vm._watcher = new Watcher(vm, updateComponent, noop)
      // mycommit-3 如果不存在之前组件
    if (!prevVnode) {
      // initial render
      vm.$el = vm.__patch__(
        // mycommit-4 67 将vnode赋值给真正的dom $el
        vm.$el, vnode, hydrating, false /* removeOnly */)
    }
```

# 数据初始化 initState(vm) //8.props data methods watch

- src/core/instance/state.js

```js
// mycommit1 处理重名的优先级 props>methods>data
if (opts.props) initProps(vm, opts.props);
if (opts.methods) initMethods(vm, opts.methods);
if (opts.data) {
}
```

- 以 initData 为例，设置响应式数据 ,在最后调用 observe 当前 data

```js
// observe data
// mycommit 递归遍历、对data做响应式处理,
observe(data, true /* asRootData */);
```

- observe 是 export 出来的 src/core/observer/index.js

```js
let ob: Observer | void;
// mycommit 创建一个ob,如果已经是响应式对象了，直接返回即可，不做重复处理
//就是判断是不是'__ob__'，任何一个响应式对象，都会有一个'__ob__'实例
// 除了设置响应式外，如果动态属性加入或删除，数组有新元素加入或删除，做变更通知
if (hasOwn(value, "__ob__") && value.__ob__ instanceof Observer) {
  // ...
  // mycommit observe 最终返回ob 实例
  return ob;
}
```

- ob 实例 是 new 的 class Observer src/core/observer/index.js

```js
// mycommit 创建响应式对象的方法
export function defineReactive (
  obj: Object,
  key: string,
  val: any,
  customSetter?: ?Function,
  shallow?: boolean
) {
  // mycommit dep 1:1 key dep和key是一对一的关系
  const dep = new Dep()
  // mycommit 如果子节点是对象，继续递归处理
  let childOb = !shallow && observe(val)
  //mycommit 重写 Object.defineProperty
  Object.defineProperty(obj, key, {})
        const value = getter ? getter.call(obj) : val
      // mycommit 首次触发render，做依赖收集
      // vue2一个组件对应一个watcher
      // dep n:n watcher
      if (Dep.target) {
        dep.depend()
```
- dep和watcher是n对n的关系是因为，在后面会有添加的watch属性，
  产生更多的watcher,所以就会造成这种情况
- 所以用depend的方式处理 在 src/core/observer/dep.js
```js
 if (childOb) {
          //mycommit 如果子ob存在，也要和当前watcher建立关系
          childOb.dep.depend()
```
## 总结
- initState的时候 优先级 props>methods>data
- initData 设置响应式数据 ,在最后调用 observe data