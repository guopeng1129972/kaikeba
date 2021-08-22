// buffer-用于tcp流、文件系统操作、以及其他上下文中与八位字节流进行交互。
// 八位字节组成数组，可以有效的在JS中存储二进制数据

// 缓冲区
const buf1 = Buffer.alloc(10);
//<Buffer 00 00 00 00 00 00 00 00 00 00> 开辟10个字节的缓冲区，一个00是2个16字节数
// 两位16进制数从00到FF，表示0-255的10进制数，也就是8 位（1个字节）的数值形式。
console.log("buf1", buf1);

const buf2 = Buffer.from("a"); //1个字节
console.log("buf2", buf2);
const buf3 = Buffer.from("中"); //3个字节
console.log("buf3", buf3);

// 图片分包 合并
const buf4 = Buffer.concat([buf2, buf3]);
console.log("buf4", buf4.toString()); //buf4 a中
