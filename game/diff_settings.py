import os

def apply(config, args):
    basename = 'game'
    if os.path.exists(f'build/{basename}.us.v10.bin'):
        version = 'us.v10'
    elif os.path.exists(f'build/{basename}.us.v11.bin'):
        version = 'us.v11'
    else:
        version = 'eu'

    config['baseimg'] = f'{basename}.{version}.decompressed.bin'
    config['myimg'] = f'build/{basename}.{version}.bin'
    config['mapfile'] = f'build/{basename}.{version}.map'
    config['source_directories'] = ['src', f'src.{version}', 'include']
