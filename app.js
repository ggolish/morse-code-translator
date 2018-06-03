const express = require('express');
const path = require("path");
const bodyParser = require("body-parser");
const apiRoute = require("./routes/api");

const app = express();
const port = process.env.PORT || 8080;

app.use(express.static(path.join(__dirname, "public")));

app.use(bodyParser.json());

app.use("/api", apiRoute);

app.get('*', (req, res) => {
  res.sendFile(path.join(__dirname, "public", "index.html"));
});

app.listen(port, () => {
  console.log("Listening on port " + port + ".");
});
