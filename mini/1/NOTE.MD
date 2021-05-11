# mini webpack

## 1.什么是 webpack

webpack 是一个打包工具，他的宗旨是一切静态资源皆可打包。(打包静态资源)

## 2.原型分析

1. 我们要制作一个打包文件的原型
2. 假设有两个 js 模块，并且假设这两个模块为复合的 commomjs 标准的 es5 模块
3. 先不管语法和模块化规范
4. 目的在于打包这两个模块成为一个可以再浏览器运行的文件，就叫 bundle.js

```js
//index.js
var add = require("add.js").default;
console.log(add(1, 2));

//add.js
exports.default = function (a, b) {
  return a + b;
};
```

假设在浏览器中执行这个程序，发现是会报错的，因为浏览器没有 require,和 export 的对象

### 1. 模拟 exports 对象

exports 对象干了什么？
首先，如果在 nodejs 打包的时候，我们会使用 sfs.readfileSync()读取 js 文件。
这样的话 js 文件会是一个字符串。如果需要将字符串中的代码运行起来，有两个方法，new Function 和 eval
eval 比 new Function 效率更高

```js
var exports = {};
eval("exports.default=function(a,b){return a+b}"); //模拟node读取代码
exports.default(1, 3);
// 从这个例子可以看出，eval("exports.default=function(a,b){return a+b}"); 是绑定exports的default方法
```

综上，运行这段代码可以将模块中的方法绑定到 exports 上，由于子模块会声明变量，
为了不污染全局，我们使用自执行函数来封装

```js
var exports={}
((exports,code){
  eval(code)
})(exports,'exports.default=function(a,b){return a+b}')
```

### 2. 模拟 require 函数

require 函数的功能比较简单，就是根据提供的 file 名称加载对应模块。
首先，是如果只有一个模块应该如何编写

```js
function require(file){
  var exports={}
  ((exports,code){eval(code)})(exports,'exports.default=function(a,b){return a+b}')
  return exports
}
var add=require('add.js').default
```

完成了固定模块，接下来稍加改动，将所有模块的文件名和代码字符串整理为一张 key-value 表
就可以根据传入的文件名加载不同的模块了。

```js
(function (list) {
  function require(file) {
    var exports = {};
    (function (exports, code) {
      eval(code);
    })(exports, list[file]);
    return exports;
  }
  require(list);
})({
  "index.js": `var add=require('add.js').default
  console.log(add(1,2))`,
  "add.js": "exports.default=function(a,b){return a+b}",
});
```

然而，真正的 webpack 生成的 bundle.js 是需要增加模块间的依赖关系的。
叫做依赖图(dependency Graph)
类似的

```js
{
  "./src/index.js": {
  "deps": { "./add.js": "./src/add.js" },
  "code": "....." },
  "./src/add.js": { "deps": {}, "code": "......"
}
}
```

另外，当使用 es6 的语法书写是，还要先转成 es5

### 总结一下 webpack 的思路

1. 分析依赖
2. es6 转 es5
3. 替换 exports 和 require

## 3. 功能实现

### 目标：将一下两个互相依赖的 ES6Module 打包为一个可以在浏览器中运行的一个 JS 文件(bundle.js)

1. 处理模块化
2. 多模块合并打包 - 优化网络请求

#### src/add.js

#### src/index.js
