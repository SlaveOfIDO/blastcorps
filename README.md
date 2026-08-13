# Blast Corps

<img src="./badges/total.svg">

A work-in-progress matching decompilation of Blast Corps `(Japan)`, `(USA)`, `(USA) (Rev 1)` and `(Europe) (En,De)`.
Currently only `(USA) (Rev 1)` is supported. Any help appreciated.

The following ROMs will be supported in the future:

| Name                           | Location             | sha1                                       | Progress                                                                                             |
|--------------------------------| ---                  | ---                                        |------------------------------------------------------------------------------------------------------|
| `Blast Corps (USA)`            | `baserom.us.v10.z64` | `185a6ef7ba1adb243278062c81a7d4e119bda58c` | 0%                                                                                                   |
| `Blast Corps (USA) (Rev 1)`    | `baserom.us.v11.z64` | `483f7161aea39de8b45c9fbc70a2c3883c4dea8c` | <img src="./badges/init.svg"> <img src="./badges/hd_code.svg"> <img src="./badges/hd_front_end.svg"> |
| `Blastdozer (Japan)`           | `baserom.jp.z64`     | `b147fdbeb661c89107c440b00dc4810508f58636` | 0%                                                                                                   |
| `Blast Corps (Europe) (En,De)` | `baserom.eu.z64`     | `460212600f8b9f0da95219c4c7330f2e626d9a7e` | 0%                                                                                                   |

This repo does not include all assets necessary for compiling the ROMs.
A prior copy of the game is required to extract the assets.

# Clone the repo

Clone recursively to initialize necessary submodules.

```
git clone https://github.com/SlaveOfIDO/blastcorps.git --recursive
```

If you cloned it without `--recursive`, you can initialize the submodule later.

```
git submodule init
git submodule update
```

# Build

Place the US Rev 1.1 ROM at the base of this repo `baserom.us.v11.z64`.

## Set up Python and splat

```
virtualenv .env
. .env/bin/activate
pip install -r requirements.txt
```

## Extract necessary files from ROM

```
make extract
```

## Build ROM

```
make
```

By default this builds `blastcorps.us.v11.z64` and verifies it matches the
original ROM byte-for-byte. Two variables control the build:

* `VERSION` - which ROM to target (currently only `us.v11` is supported).
* `NON_MATCHING` - set to `1` to allow some more portable code that does not
  produce a matching ROM (default `0`, matching build). *EXPERIMENTAL*

```
make VERSION=us.v11 NON_MATCHING=1
```

# Related

* retroplatic's [blastcorps](https://github.com/retroplastic/blastcorps)

  The base of this repo

* mkst's [blastcorps](https://github.com/mkst/blastcorps)

  Initial set up of splat and Makefile build this repo is based on.

* queueRAM's [blast_corps_docs](https://github.com/queueRAM/blast_corps_docs)

  The original repository this is based upon. The content can be found in `docs` and `tools`.

* queueRAM's [BlastCorpsEditor](https://github.com/queueRAM/BlastCorpsEditor)

  A C# level editor for blast corps.

* queueRAM's [sm64tools](https://github.com/queueRAM/sm64tools)

  A N64 rom manipulation tool silimar to splat, written in C.

* mkst's [gzip](https://github.com/mkst/gzip) branch

  Backport of the pre-1.5 bug behaviour of gzip to support the rare gzip format.

* ethteck's [splat](https://github.com/ethteck/splat)

  A binary splitting tool, used as subrepository in this project.

* [n64decomp](https://github.com/n64decomp)

  A collection of N64 decompilation projects.

* queueRAM's [Texture](https://github.com/queueRAM/Texture64)

  Can be used to view raw textures extracted from gzip. Works with mono.

