
# AQUA-2.X-x86
This is the repository for the AQUA 2.X x86 kernel

# How to run (Linux)
First, download this repository with

```bash
$ git clone https://github.com/obiwac/AQUA-2.X-x86
$ cd AQUA-2.X-x86
```

Make sure that you have all the requiered dependencies by running

```bash
$ make download
```

**NOTE** This uses `apt` to install the packages so it will only work on Debian/Ubuntu based systems.
Then, build it with

```bash
$ make
```

This will build it with an `i686-elf` cross compiler if you have one (if not you can automatically compile it with `$ make cross-compiler`), but will instead compile with `gcc -m32` if it doesn't detect it.
Then you can setup your Virtual Box VM or what not with the aqua.iso in aqua/.

You can automatically create a Virtual Box VM by running

```bash
$ make vm-setup
```

And you can then run it with

```bash
$ make test
```

If you want to build AQUA with the PCI database, run

```bash
$ make pci-database
```

to download the latest PCI-ID and create a database.

# Minimum / recommended Virtual Box VM specs

| Specification  | Minimum       | Recommended    |
| -------------- | -------------:| --------------:|
| RAM            | 512 MB        | 1024 MB        |
| VRAM           | 9 MB          | 12 MB          |
| Virtualization | VT-x / AMD-v  | VT-x / AMD-v   |
| Storage        | 2 GB          | 2 GB           |
| Audio          | ICH AC97      | Intel HD Audio |
| Networking     | RTL8139       | Intel i217     |

**NOTE** the "minimum" specs are not necessarily the *bare* minimum but are the minimum you will need if you want to be future-proof.
Some of these recommended features are not even partially or fully implemented yet.
