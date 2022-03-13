def Settings( **kwargs ):
  return {
    'flags': [ 
        '-x', 
        'c', 
        '-std=c99',
        '-Wextra', 
        '-Wno-unused-variable',
        '-Werror', 
        '-Wall',
        ],
  }
