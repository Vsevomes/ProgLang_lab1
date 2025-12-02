# ProgLang_lab1

## Build project

```bash
mkdir build
cd build
cmake ..
make -j$(nproc)
```

## Execute project example

```bash
./ProgLangLab1 <input_file1> [input_file2 ... input_fileN] [-o <output_directory>]
```

I recommend you to use `tests` directory for your code examples, because its containe script of visualisation of dot files with graphs. But if you need, you can copy it in directory you want to work with.

For graph visualistion in `tests` directory:

```
./dot.sh [directory] [output_format]
```

Write `./dot.sh` to get `.png` files in current directory.
