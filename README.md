# Morse Code Translator

A Morse Code translator API implemented in C. Translates plain text into
binary digits representing the various sequences, listed below. Contains an Express server that uses the API as a backend.

## Usage information:
```
api/morse [path]
```
* If a path to a file is specified, the file will be read and converted to Morse Code, which will be outputed to standard output.
* If a path is not specified, a simple REPL will run, where the user can interactively translate messages into Morse Code.

## Build:
To build the project, simply run ```make morse``` in the ```api``` directory, ```npm install``` in the root directory, and then run the server using ```node app.js```. Navigate to ```http://localhost:8080``` to view a demo frontend that sends requests to the server.

## Sequences:
* ```1``` = dot
* ```111``` = dash
* ```0``` = intracharacter pause
* ```000``` = pause between letters
* ```0000000``` = pause between words

## License:
This project is distributed under the MIT license.

## Author
© 2018 Gage Golish
