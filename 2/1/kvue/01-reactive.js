// defineReactive 的功能是封装了一个方法，使给传进来的obj一个响应式的属性
function defineReactive(obj, key, val) {
  //递归，如果val 即监听的对象的元素是一个对象，形如obj.baz.n,就先对子元素进行监听
  observe(val); //get bas; get n
  Object.defineProperty(obj, key, {
    get() {
      console.log("get", key);
      return val;
    },
    set(newVal) {
      if (newVal !== val) {
        console.log("set", key);
        val = newVal;
        // 当用户直接替换属性时，添加监听
        observe(newVal);
      }
    },
  });
}
// 遍历响应式处理，即处理的响应式很多，需要监听当前处理过程
function observe(obj) {
  if (typeof obj !== "object" || typeof obj == null) {
    return;
  }
  Object.keys(obj).forEach((key) => defineReactive(obj, key, obj[key]));
}

function set(obj, key, val) {
  defineReactive(obj, key, val);
}
const obj = {
  foo: "foo",
  bar: "bar",
  baz: {
    n: 1,
  },
};
// defineReactive(obj, "foo", "foo");
observe(obj);
// obj.foo;
// obj.baz = { n: 22 }; //set bas;get bas
// obj.baz.n;
// obj.tool = "tool";
set(obj, "tool", "tool");
obj.tool;
