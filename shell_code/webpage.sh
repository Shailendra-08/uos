# downlaod web page

echo "Enter the Url"
read url

wget -O downlaod_webpage.html "$url"

if [ $? -eq 0 ]; then
    echo "Webpage downlaod successfully"
else
    echo "Webpage downlaod unsuccessfull"
fi