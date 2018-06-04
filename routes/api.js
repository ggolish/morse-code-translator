const express = require("express");
const router = express.Router();
const MorseTranslator = require("../api/MorseTranslator");

router.post('/translate', (req, res) => {
  if(req.body.plaintext && req.body.plaintext != '') {
    // Path is relative to root directory
    const translator = new MorseTranslator('./api/libmorse.so');
    res.send(translator.translate(req.body.plaintext));
  } else {
    res.send("Data not received.");
  }
});

module.exports = router;
