cc = meson.get_compiler('c')
math = cc.find_library('m', required : true)


executable('heapsort', 'heapsort.c', install : true, dependencies: [math])
executable('quicksort', 'quicksort.c', install : true, dependencies: [math])
executable('mergesort', 'mergesort.c', install : true, dependencies: [math])
executable('selectionsort', 'selectionsort.c', install : true, dependencies: [math])
executable('shellsort', 'shellsort.c', install : true, dependencies: [math])
executable('insertionsort', 'insertionsort.c', install : true, dependencies: [math])
