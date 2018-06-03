const fastcall = require("fastcall");
const Library = fastcall.Library;

class MorseTranslator {
  constructor() {
    this.lib = new Library('./libmorse.so')
      .function('char* morse_translate(char* plaintext)');
  }

  translate(plaintext) {
    return fastcall.readCString(
      this.lib.interface.morse_translate(fastcall.makeStringBuffer(plaintext))
    );
  }
}

module.exports = MorseTranslator;
