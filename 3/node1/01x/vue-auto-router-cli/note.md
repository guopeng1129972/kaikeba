# 创建工程

```bash
mkdir vue-auto-router-cli
cd vue-auto-router-cli
npm init -y
npm i commander download-git-repo ora handlebars figlet clear chalk open -s
```

# bin/kkb.js

> 指定脚本解释器为 node
> #!/usr/bin/env node console.log('cli.....')

# package.json

"bin": {
"kkb": "./bin/kkb.js"
},

# 将 npm 模块链接到对应的运行项目中去

npm link

# 删除的情况

```bash
ls /usr/local/bin/
rm /usr/local/bin/kkb
```

# 定制命令行界面

- kkb.js

```js
#!/usr/bin/env node
const program = require('commander') program.version(require('../package').version)
program
.command('init <name>') .description('init project') .action(name => {
console.log('init ' + name)
}) program.parse(process.argv)

```

# 打印欢迎界面

```js

```
