

checkfile() {
    local filepath="$1"

    if [ -f "$filepath" ]; then
        echo "File exist in the given Path"
    else 
        echo "File does not exist in the given path"
    fi

}



echo "Enter the path of the file:"
read  filepath

checkfile "$filepath"