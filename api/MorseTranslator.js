const fastcall = require("fastcall");
const Library = fastcall.Library;

class MorseTranslator {
  constructor(path) {
    this.lib = new Library(path)
      .function('char* morse_translate(char* plaintext)');
  }

  translate(plaintext) {
    return fastcall.ref.readCString(
      this.lib.interface.morse_translate(fastcall.makeStringBuffer(plaintext))
    );
  }
}

module.exports = MorseTranslator;
