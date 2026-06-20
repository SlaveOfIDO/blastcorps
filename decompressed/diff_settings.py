import os

def apply(config, args):
    config['baseimg'] = f'decompressed.us.v11.bin'
    config['myimg'] = f'build/decompressed.us.v11.bin'
    config['mapfile'] = f'decompressed.map'
    config['source_directories'] = ['src', 'include']
