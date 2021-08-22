const http = require("http");
const fs = require("fs");
const server = http.createServer((require, response) => {
  // console.log("require");
  // console.log(response);
  // getPrototypeChina(response);
  const { url, method, headers } = require;
  if (url === "/" && method === "GET") {
    fs.readFile("index.html", (err, data) => {
      if (err) {
        response.writeHead(500, { "Content-Type": "text/plain;charset=utf-8" });
        response.end("500 服务器错误");
        return;
      }
      response.statusCode = "200";
      response.setHeader("Content-Type", "text/html");
      response.end(data);
    });
  } else if (url === "/user" && method == "GET") {
    response.writeHead(200, { "Content-Type": "application/json" });
    response.end(JSON.stringify({ name: "tom" }));
  } else if (method == "GET" && headers.accept.indexOf("image/*") != -1) {
    // 统一描述所有图片请求
    // 使用fs.readFile('')合理吗？ 不合理，太占内存，比如图片100kb*10 网页就需要这么多内存，也很费时间
    // 所以使用fs.readFile('')不合理,需要使用流
    fs.createReadStream("." + url).pipe(response);
  } else {
    response.statusCode = "404";
    response.setHeader("Content-Type", "text/plain;charset=utf-8");
    response.end("404 页面没找到");
  }
});

server.listen(3000, () => {
  console.log("server is ok at 3000");
});
// pm2 kill

function getPrototypeChina(obj) {
  let protoChina = [];
  while ((obj = Object.getPrototypeOf(obj))) {
    protoChina.push(obj);
  }
  return protoChina;
}
