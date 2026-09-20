# Usage

CEncode [1] [2] [3] [4] [5]

[1] --> encoder to use.
## Supported encoders:
ASCII, ASCII85/Base85, Hexadecimal, Binary, Morse Code, URL

[2] --> encoder flag
## Encoder flags:
-d --> decode
-e --> encode

[3] --> file path or text to encode/decode
ex:
/home/user/test.txt
or
"Test message"
or
Test

[4] --> output (file path or 'console')
ex: /home/user/test2.txt --> writes the result to the file
console --> displays the result in the terminal window.

### Optional argument
#### For binary encoding/decoding:
-text --> binary text representation
-decimal --> binary decimal representation
#### For hex
-add-spaces --> separates the hex values by a space
