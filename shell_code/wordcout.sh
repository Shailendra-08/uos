# Generate a word frequency list for wonderland.txt. Hint: use grep, tr, sort, uniq (or anything else that you want)

grep -oE '\w+' input.txt | sort | uniq -c | sort -nr


2