// stream相当于一根导管，将导出指定数据，导入指定文件
const fs = require("fs");
const rs = fs.createReadStream("./1.jpg");
const ws = fs.createWriteStream("./2.jpg");
rs.pipe(ws);
