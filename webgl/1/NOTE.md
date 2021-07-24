# 概述

牛逼

# webgl 最短教程

- 设置 css 是不能通过 gpu 动态修改的，可以理解为在页面完成 render 之后不再修改

```css
#canvas {
  background-color: antiquewhite;
}
```

```js
const gl = canvas.getContext("webgl"); //三维
//使用 gl.clearColor(),设置颜色缓冲区 COLOR_BUFFER_BIT
gl.clearColor(1, 0, 0, 1); //rgba(0-1)相当于0-255 相当于设置 COLOR_BUFFER_BIT
gl.clear(gl.COLOR_BUFFER_BIT); //这块clear，想到与生效
```

# api

WebGLRenderingContext.clearColor() 方法用于设置清空颜色缓冲时的颜色值。
void gl.clearColor(red, green, blue, alpha); //不透明度 （0-1）

# 1.4 css 颜色转 webgl 颜色

主要就是学习，怎么把 css 字符串的样式颜色转换成 webgl 的颜色

- 获取数据

```js
const cssColor = "rgba(255,100,88,1)";
const reg = RegExp(/\((.*)\)/);
/*  1.\(字符中的(,反斜杠表示作为参数查找
          2.正则中的() 表示捕获括号，根据参数表示不同意思
            (.) 表示除回车之外的所有字符；
            (.*) 表示匹配0个或者多个；  
      */
const rgbaStr = reg.exec(cssColor)[1];
```

- 加工并写入数据

```js
const rgba = rgbaStr.split(",").map((n) => parseInt(n));
console.log(rgba);
gl.clearColor(rgba[0] / 255, rgba[1] / 255, rgba[2] / 255, rgba[3]);
gl.clear(gl.COLOR_BUFFER_BIT);
```
