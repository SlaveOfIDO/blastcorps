import os

def apply(config, args):
    config['baseimg'] = f'hd_code.bin'
    config['myimg'] = f'build/hd_code.bin'
    config['mapfile'] = f'hd_code.map'
    config['source_directories'] = ['src', 'include']
