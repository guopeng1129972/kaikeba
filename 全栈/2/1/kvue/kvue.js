function defineReactive(obj, key, val) {
  //递归，如果val 即监听的对象的元素是一个对象，形如obj.baz.n,就先对子元素进行监听
  observe(val); //get bas; get n
  const dep = new Dep();
  Object.defineProperty(obj, key, {
    get() {
      // console.log("get", key);
      // 依赖收集
      Dep.target && dep.addDep(Dep.target);
      return val;
    },
    set(newVal) {
      if (newVal !== val) {
        // console.log("set", key);
        val = newVal;
        // 当用户直接替换属性时，添加监听
        observe(newVal);
        // update() 触发依赖
        dep.notify();
      }
    },
  });
}
// 遍历响应式处理，即处理的响应式很多，需要监听当前处理过程
function observe(obj) {
  if (typeof obj !== "object" || typeof obj == null) {
    return;
  }
  //预留对数组的处理，先表示对对象的处理逻辑
  new Observer(obj);
}
// 能够将传入对象中的所有key代理到指定对象上
function proxy(vm) {
  Object.keys(vm.$data).forEach((key) =>
    Object.defineProperty(vm, key, {
      get() {
        return vm.$data[key];
      },
      set(v) {
        vm.$data[key] = v;
      },
    })
  );
}
class Compile {
  // 宿主元素与KVue实例
  constructor(el, vm) {
    this.$vm = vm;
    //获取DOM元素
    this.$el = document.querySelector(el);
    if (this.$el) {
      this.compile(this.$el);
    }
  }
  // 遍历node,判断节点类型，做不同处理
  compile(node) {
    const childNodes = node.childNodes;
    Array.from(childNodes).forEach((n) => {
      // 判断节点类型
      if (this.isElement(n)) {
        // 如果子元素也是childNodes需要递归
        // console.log("编译节点", n.nodeName);
        this.compileElemet(n);
        if (n.childNodes.length > 0) {
          this.compile(n);
        }
      } else if (this.isInter(n)) {
        // console.log("编译文本", n.textContent);
        // 动态插值表达
        this.compileText(n);
      }
    });
  }
  isElement(n) {
    return n.nodeType === 1;
  }
  isInter(n) {
    return n.nodeType === 3 && /\{\{(.*)\}\}/.test(n.textContent);
  }
  //编译插值文本
  compileText(n) {
    console.log(RegExp.$1);
    // n.textContent = this.$vm[RegExp.$1];
    this.update(n, RegExp.$1, "text");
  }
  //编译元素：遍历它的所有特性
  compileElemet(n) {
    const attrs = n.attributes;
    Array.from(attrs).forEach((attr) => {
      // k-text='xxx' name k-text ,value xxx
      const attrName = attr.name;
      const exp = attr.value;
      if (this.isDir(attrName)) {
        const dir = attrName.substring(2);
        // 判断当前的this下有没有dir(test)这个表达式，如果有就执行，如果没有就不会执行
        this[dir] && this[dir](n, exp);
      } else if (this.isEvent(attrName)) {
        const dir = attrName.substring(1);
        this[dir] && this[dir](n, exp);
      }
    });
  }
  update(node, exp, dir) {
    // 1.init
    const fn = this[dir + "Updater"];
    fn && fn(node, this.$vm[exp]);
    // 2.update
    new Watcher(this.$vm, exp, (val) => {
      fn && fn(node, val);
    });
  }
  // k-text
  text(node, exp) {
    this.update(node, exp, "text");
  }
  textUpdater(node, val) {
    node.textContent = val;
  }
  // k-html
  html(node, exp) {
    this.update(node, exp, "html");
  }
  htmlUpdater(node, val) {
    node.innerHTML = val;
  }
  // @click
  click(node, exp) {
    // debugger;
    node.addEventListener("click", this.$vm.$methods[exp], true);
  }

  isDir(attrName) {
    return attrName.startsWith("k-");
  }

  isEvent(attrName) {
    return attrName.startsWith("@");
  }
}
// 监听响应式数据,根据传入的值做相应的处理
class Observer {
  constructor(obj) {
    // 根据传入的值做相应的处理，如果是arr就按照arr的思路去处理响应式，否则使用对象的方法
    if (Array.isArray(obj)) {
      console.log("arr todo");
    } else {
      this.walk(obj);
    }
  }
  // 这里预留了对如果是数组的话的处理，以及如果是数组的话，添加walk方法处理
  walk(obj) {
    Object.keys(obj).forEach((key) => defineReactive(obj, key, obj[key]));
  }
}

class KVue {
  constructor(options) {
    // 0.保存选项
    this.$options = options;
    this.$data = options.data;
    this.$methods = options.methods;
    // 1.对data进行响应式处理
    observe(options.data);
    // 2.代理
    proxy(this);
    // 3.编译
    new Compile(options.el, this);
  }
}

class Watcher {
  constructor(vm, key, updater) {
    this.vm = vm;
    this.key = key;
    this.updater = updater;
    // 在watcher上创建dep的target绑定this,然后get过程触发
    Dep.target = this;
    this.vm[this.key];
    Dep.target = null;
  }
  // 将来会被Dep调用
  update() {
    this.updater.call(this.vm, this.vm[this.key]);
  }
}
// Dep类 实现对watcher的管理，保存watcher实例的依赖的类
class Dep {
  constructor() {
    this.deps = [];
  }
  // 这里的dep就是watcher的实例
  addDep(dep) {
    this.deps.push(dep);
  }
  notify() {
    this.deps.forEach((dep) => dep.update());
  }
}
