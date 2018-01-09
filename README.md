
# AQUA-2.X-x86
This is the repository for the AQUA 2.X x86 kernel

# How to run (Linux)
First, download this repository with

```bash
$ git clone https://github.com/obiwac/AQUA-2.X-x86
$ cd AQUA-2.X-x86
```

Then, build it with

```bash
$ make
```

This will build it with an `i686-elf` cross compiler if you have one, but will instead compile with `gcc -m32` if it doesn't detect it.
Then you can setup your Virtual Box VM or what not with the aqua.iso in aqua/.

# Minimum / recommended Virtual Box VM specs

| Specification  | Minimum       | Recommended    |
| -------------- | -------------:| --------------:|
| RAM            | 512 MB        | 1024 MB        |
| VRAM           | 9 MB          | 12 MB          |
| Virtualization | VT-x / AMD-v  | VT-x / AMD-v   |
| Storage        | 2 GB          | 2 GB           |
| Audio          | ICH AC97      | Intel HD Audio |
| Networking     | Intel 8254x   | Intel 8254x    |

**NOTE** the "minimum" specs are not necessarily the *bare* minimum but are the minimum you will need if you want to be future-proof.
Some of these recommended features are not even partially or fully implemented yet.
