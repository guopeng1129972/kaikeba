# 大圣实战项目

## 1.1 项目介绍

主要是关于一些项目功能的学习

## 1.2 文件上传功能

项目亮点

- 1.文件的校验
  安装 hexdump 插件查看文件的二进制表示
  点击右上角`0110`的图标查看图片的二进制码
  00000000: 89 50 4E 47 0D 0A 1A 0A 00 00 00 0D 49 48 44 52 .PNG........IHDR
  可以发现`.png是 89 50 4E 47`，因此判断这个就是最好的方法
  `.jpg FF D8 开始 FF 09结尾`
  `.gif 47 49 46 38 38 61 3C`

## 03-断点续传（点播）

就是在前端将图片切片，分段进行上传，
如果中间中断，在服务器上找到断点，继续上传

### 什么是秒传？

如果服务器上存在之前传过的相同图片，比对存在之后，就不需要传了
那么问题来了。如果比对的是名字的话，存在重复怎么办？

## 04-大文件指纹计算

- 1.在浏览器渲染的每一帧的空闲时间进行 MD5 计算
- 2.选择大文件中几块部分进行 md5，比对

## 05-并发数控制逻辑（点播）

- 1.并发数控制+错误重试 （头条面试）
  比如处理 100 个任务，对外只暴露 4 个，1 处理完处理 5，2 处理完处理 6...等等
  如果都出现错误就返回错误回调
- 2.慢启动（借鉴 TCP 策略）
  TCP 慢启动策略，先传一个比较小的块，然后根据成功的时间进行下一次的包大小，
  利用好网速

## 06-项目搭建（点播）

```bash
mkdir project-full && cd project-full
npx create-nuxt-app front
```

- 回显
  ✨ Generating Nuxt.js project in front
  ? Project name: front
  ? Programming language: JavaScript
  ? Package manager: Npm
  ? UI framework: Element
  ? Nuxt.js modules: Axios - Promise based HTTP client
  ? Linting tools: ESLint
  ? Testing framework: Jest
  ? Rendering mode: Universal (SSR / SSG)
  ? Deployment target: Server (Node.js hosting)
  ? Development tools: jsconfig.json (Recommended for VS Code if you're not using typescript)
  ? Continuous integration: GitHub Actions (GitHub only)
  ? What is your GitHub username? guopeng1129972
  ? Version control system: Git

### 创建服务器框架

```bash
cd project-full
mkdir server && cd server
npm init egg --type=simple
```

- 回显
  `cookie security keys` 主要用于加密的
  ? project name server
  ? project description
  ? project author guopeng1129972
  ? cookie security keys 1629007426613_3473
- 安装 server 的依赖

```bash
cd server && npm install
npm install husky ^4.2.3 --save-dev
```

## 07-代码规范+husky 设置（点播）

- project-full/server/.eslintrc
  配置不用分号结尾

```js
  "rules":{
    "semi":["error","never"]
  }
// project-full/server/package.json 中配置-- --fix 会自动修正在commit中的错误点
  "test": "npm run lint -- --fix && npm run test-local",
```
- 代码提交commit规范
就是一种规范 commit提交的东西
```bash
npm install -g commitizen
cd server
commitizen init cz-conventional-changelog --save-dev --save-exact
```
