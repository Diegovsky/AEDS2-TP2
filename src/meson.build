cc = meson.get_compiler('c')
math = cc.find_library('m', required : true)


runnerlib = library('runnerlib', sources: [ 'runner.c' ])

executable('heapsort', 'heapsort.c',           link_with: runnerlib, install : true, dependencies: [math])
executable('quicksort', 'quicksort.c',         link_with: runnerlib, install : true, dependencies: [math])
executable('mergesort', 'mergesort.c',         link_with: runnerlib, install : true, dependencies: [math])
executable('selectionsort', 'selectionsort.c', link_with: runnerlib, install : true, dependencies: [math])
executable('shellsort', 'shellsort.c',         link_with: runnerlib, install : true, dependencies: [math])
executable('insertionsort', 'insertionsort.c', link_with: runnerlib, install : true, dependencies: [math])
