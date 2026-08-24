import os

import n64img.image
from splat.segtypes.segment import Segment
from splat.util import options
import subprocess


def split_segment_bytes(subsegments, decoded_bytes: bytes):
    segment_bytes = []
    separators = []
    for segment in subsegments:
        separators.append(segment[0])
    separators.append(len(decoded_bytes))

    for i in range(len(subsegments)):
        from_slice = separators[i]
        to_slice = separators[i + 1]
        segment_bytes.append(decoded_bytes[from_slice:to_slice])

    return segment_bytes


def get_gzip_original_filename(gz_file_path) -> str | None:
    with open(gz_file_path, "rb") as f:
        header = f.read(10)
        magic1, magic2, method, flags = header[0], header[1], header[2], header[3]
        assert magic1 == 0x1F and magic2 == 0x8B, f"{gz_file_path} is not a gzip file"

        FEXTRA = 0x04
        FNAME = 0x08

        if flags & FEXTRA:
            xlen = int.from_bytes(f.read(2), "little")
            f.read(xlen)

        if not flags & FNAME:
            return None

        name_bytes = bytearray()
        while (b := f.read(1)) not in (b"", b"\x00"):
            name_bytes += b
        return name_bytes.decode("latin-1")
    return None


def get_png_writer(file_type: str):
    match file_type:
        case "rgba16":
            return n64img.image.RGBA16
        case "rgba32":
            return n64img.image.RGBA32
        case "ia8":
            return n64img.image.IA8
        case "ia16":
            return n64img.image.IA16
        case _:
            return None


class N64SegRzip(Segment):
    def out_path(self):
        # Same location/naming as the plain "bin" segtype, so this segment's
        # compressed bytes still get glob-matched and linked into the final
        # ROM by the Makefile (see BIN_FILES) and get a linker entry (below),
        # exactly as if this were still a plain `bin` segment.
        return options.opts.asset_path / self.dir / f"{self.name}.bin"

    def get_linker_entries(self):
        from splat.segtypes.linker_entry import LinkerEntry

        path = self.out_path()
        return [
            LinkerEntry(
                self,
                [path],
                path,
                self.get_linker_section_order(),
                self.get_linker_section_linksection(),
                self.is_noload(),
            )
        ]

    def write_png(self, type_str: str, width: int, height: int, decompressed_file_name: str, image_bytes: bytes):
        writer_class = get_png_writer(type_str)

        png_name = decompressed_file_name.replace("raw", "png")
        png_dir_path = options.opts.asset_path / self.dir / "png" / "rzip"
        png_dir_path.mkdir(exist_ok=True, parents=True)
        png_file_path = png_dir_path / png_name

        writer_class(image_bytes, width, height).write(png_file_path)

    def write_png_segments(self, decompressed_file_name: str, segment_bytes: list[bytes], subsegments):
        assert len(segment_bytes) == len(subsegments)

        for i in range(len(segment_bytes)):

            assert len(subsegments[i]) == 4

            type_str = subsegments[i][1]
            width = subsegments[i][2]
            height = subsegments[i][3]

            writer_class = get_png_writer(type_str)

            png_name = decompressed_file_name.replace("raw", f"{i}.png")
            png_dir_path = options.opts.asset_path / self.dir / "png" / "rzip"
            png_dir_path.mkdir(exist_ok=True, parents=True)
            png_file_path = png_dir_path / png_name

            writer_class(segment_bytes[i], width, height).write(png_file_path)

    def split(self, rom_bytes):
        split_dir_path = options.opts.asset_path / self.dir / "split"
        split_dir_path.mkdir(exist_ok=True, parents=True)
        gz_file_path = split_dir_path / f"{self.name}.gz"

        # Write compressed
        compressed_bytes = rom_bytes[self.rom_start: self.rom_end]
        with open(gz_file_path, "wb") as f:
            f.write(compressed_bytes)

        # Also write the still-compressed bytes to this segment's normal
        # out_path(), so the ROM build (which links whatever lands in
        # assets/*.bin, see out_path() above) still reconstructs this range
        # byte-for-byte, same as a plain "bin" segment would.
        out_path = self.out_path()
        out_path.parent.mkdir(exist_ok=True, parents=True)
        with open(out_path, "wb") as f:
            f.write(compressed_bytes)

        # Decompressed
        subprocess.call(["gzip", "-d", "-k", "-N", "-f", gz_file_path])

        decompressed_file_name = get_gzip_original_filename(gz_file_path)
        decompressed_file_name = decompressed_file_name.split("/")[-1]

        decompressed_file_path = options.opts.asset_path / self.dir / "split" / decompressed_file_name

        decoded_dir_path = options.opts.asset_path / self.dir / "uncompressed"
        decoded_dir_path.mkdir(exist_ok=True, parents=True)

        new_decompressed_file_path = decoded_dir_path / decompressed_file_name

        # Move result to uncompressed folder
        os.rename(decompressed_file_path, new_decompressed_file_path)

        # Write PNG
        if len(self.yaml) == 6 or isinstance(self.yaml, dict):

            with open(new_decompressed_file_path, "rb") as f:
                image_bytes = f.read()

            if isinstance(self.yaml, list):
                # Single segment
                type_str = self.yaml[3]
                width = self.yaml[4]
                height = self.yaml[5]
                self.write_png(type_str, width, height, decompressed_file_name, image_bytes)
            elif isinstance(self.yaml, dict):
                subsegments = self.yaml["subsegments"]
                segment_bytes = split_segment_bytes(subsegments, image_bytes)
                self.write_png_segments(decompressed_file_name, segment_bytes, subsegments)
