const express = require("express");
const router = express.Router();
const MorseTranslator = require("../api/MorseTranslator");

router.post('/translate', (req, res) => {
  // Path is relative to root directory
  const translator = new MorseTranslator('./api/libmorse.so');
  res.send(translator.translate(req.body.plaintext));
});

module.exports = router;
