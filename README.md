# dbc_parser
Program that generates executable C-code for reading and writing CAN-Messages defined in *.dbc-files

![grafik](https://user-images.githubusercontent.com/11078162/222678024-8b9fc32b-88bc-4bc1-ae9c-b44775250823.png)

This message is parsed to following C-defines that can be used to fill/read the can-frame buffer
![grafik](https://user-images.githubusercontent.com/11078162/222678549-97e1b76c-7cd6-490b-ad54-7ef0c6977a2a.png)

Supported are signales singned and unsigned integers in all lengths (1 bit up to 64 bit), IEEE Float and IEEE Double. The signals don't necessarily have to be byte-aligned. Signal factor and offset are applied automatically as well as the negative sign. The message id, dlc and extended-flag are exported as well as signal unit, factor, min- and max-values. The endianess is accounted for automatically.

![grafik](https://user-images.githubusercontent.com/11078162/222682695-2125f74d-0085-4c23-94f1-cfe6d6eec963.png)

![grafik](https://user-images.githubusercontent.com/11078162/222682865-6c81ce43-238c-4696-a9a8-6b3040f08400.png)


## Usage
```
Usage:
   dbc_parser [dbc_file.dbc] [h_file.h] [options]
   Options:
      -h | Output this help
      -v | verbose
      -d | without documentation (doxygen)
```
### Example
```bash
dbc_parser test_file.dbc test_file.h
```
Reads the fest_file.dbc and outputs the C-defines into test_file.h

#### Implementation
Set signal to data-array

![grafik](https://user-images.githubusercontent.com/11078162/222683370-8fa1095f-8eed-4c44-bb5f-01f9baadb0d5.png)

Get signal from data-array

![grafik](https://user-images.githubusercontent.com/11078162/222683543-1d78d8f9-83ef-4b4b-bcae-b2e9f5f6f7b1.png)


## Compiling the dbc_parser
```
mkdir build
cd build
cmake ..
make
```
