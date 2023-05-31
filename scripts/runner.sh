#!/usr/bin/env zsh
set -e
file=$1
curfolder=$(dirname $(realpath $0))
if [[ ! -f $file ]]; then
    echo 'File not found!'
    return -1
fi

file=$(realpath $file)

mkdir -p data
cd data

foldername=$(basename -- "$file")
if ! mkdir -p $foldername; then
    echo 'Cannot create directory!'
    return -1
fi
pyscript=$(realpath "$curfolder/dados.py")
cd $foldername

for mode in rand cres decres; do
    mkdir -p $mode
    pushd $mode
    report=../"$mode"_report.txt
    echo '' > $report
    for N in 20 500 5000 10000 2000000; do
        if [[ $foldername == quicksort ]] && [[ $N -eq 200000 ]] && [[ $mode != rand ]]; then
            continue
        fi
        fname="$foldername"_"$N"_"$mode".txt
        "$file" "$N" "$mode" | tee "$fname"
        python "$pyscript" "$fname" >> "$report"
        echo '' >> "$report"
    done
    popd
done
