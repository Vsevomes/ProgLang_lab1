# ProgLang_lab3

## Build project

```bash
mkdir build
cd build
cmake ..
make -j$(nproc)
```

## Execute project example

```bash
./ProgLangLab1 <input1> -o <out.asm> [--dump-cfg]
```

I recommend you to use `tests` directory for your code examples, because its containe script of visualisation of dot files with graphs, if you use `--dump-cfg` flag. But if you need, you can copy it in directory you want to work with.

For graph visualistion in `tests` directory:

```
./dot.sh [directory] [output_format]
```

Write `./dot.sh` to get `.png` files in current directory.

For compile and execute generated `.asm` file in `architecture` directory use:

```
./build_script.sh
./execute_script.sh
```

For use without changes translate to asm `trans_example.txt` or you should change filename in `sh`.