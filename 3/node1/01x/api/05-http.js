const http = require("http");
const fs = require("fs");
const server = http.createServer((require, response) => {
  // console.log("require");
  // console.log(response);
  // getPrototypeChina(response);
  const { url, method } = require;
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
