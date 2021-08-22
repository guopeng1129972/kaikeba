const fs = require("fs");
// 同步操作
{
  const data = fs.readFileSync("./conf.json");
  console.log("readFileSync data", data.toString());
}
{
  // 异步操作
  fs.readFile("./conf.json", (err, data) => {
    if (err) throw err;
    console.log("readFile data", data.toString());
  });
  console.log("end");
}
// async await 与Generator

{
  // 如何封装异步操作为async await的形式
  async () => {
    const fs = require("fs");
    const { promisify } = require("util");
    const readFile = promisify(fs.readFile);
    const data = await readFile("./conf.json");
    console.log("async await data", data.toString());
  };
}
