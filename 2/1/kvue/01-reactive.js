// defineReactive 的功能是封装了一个方法，使给传进来的obj一个响应式的属性
function defineReactive(obj, key, val) {
  Object.defineProperty(obj, key, {
    get() {
      console.log("get", key);
      return val;
    },
    set(newVal) {
      if (newVal !== val) {
        console.log("set", key);
        val = newVal;
      }
    },
  });
}

const obj = {};
defineReactive(obj, "foo", "foo");
obj.foo;
