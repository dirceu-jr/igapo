const fs = require("fs");
const { parse } = require("csv-parse");

var by_codigo_and_poluente = {};

fs.createReadStream("../data/2020PR.csv")
  .pipe(parse({ delimiter: ",", from_line: 2, encoding: "utf8" }))
  .on("data", function (row) {
    var id = row[3] + "_" + row[4];

    if (by_codigo_and_poluente[id] == undefined) {
      by_codigo_and_poluente[id] = [];
    }

    var to_add = [row[0], row[1], row[5]];

    by_codigo_and_poluente[id].push(to_add);
  }).on("end", function () {

    for (index in by_codigo_and_poluente) {

      // TODO:
      // save ordered
      const filename = "../data/" + index + ".json";
      let data = JSON.stringify(by_codigo_and_poluente[index]);
      fs.writeFileSync(filename, data);

      console.log(index);
    }
    
  });

  // [
  //   '2020-12-22',
  //   '10:00:00',
  //   'PETROSIX',
  //   'PR09',
  //   'SO2',
  //   '0',
  //   'ppb',
  //   'automatica'
  // ]
  