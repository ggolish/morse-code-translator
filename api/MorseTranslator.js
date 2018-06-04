const fastcall = require("fastcall");
const Library = fastcall.Library;

class MorseTranslator {

  constructor(path) {
    this.lib = new Library(path)
      .function('char* morse_translate(char* plaintext)')
      .function('void morse_free()');
  }

  translate(plaintext) {
    const cstring = fastcall.makeStringBuffer(plaintext + '.');
    const cstring2 = this.lib.interface.morse_translate(cstring);
    const rv = (fastcall.ref.isNull(cstring2)) ? 'Data not received.' : fastcall.ref.readCString(cstring2);
    this.lib.interface.morse_free();
    return rv;
  }
  
}

module.exports = MorseTranslator;
