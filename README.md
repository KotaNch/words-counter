# word-counter

Small C program that counts lines, words and bytes in files.

## Build

```bash
make
```

Needs `clang`

## Usage

```bash
./word-counter ex.txt
./word-counter -l ex.txt
./word-counter -wc ex.txt e.txt
```


Flags:
- `-l` lines
- `-w` words
- `-c` bytes

(No flags means all three)


## Tests

```bash
make test
```


