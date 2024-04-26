// calculator using script

echo "Enter the number1"
read no1
echo "Enter the number2"
read no2
i="y"
while [ $i = "y" ]
do
    echo "1.addition"
    echo "2.subtratcion"
    echo "3.Multiplication"
    echo "4.Division"
    read ch
    case $ch in
        1)sum=`expr $no1 + $no2`
        echo "Sum="$sum;;
        2)sub=`expr $no1 - $no2`
        echo "Sub="$sub;;
        3)Mul=`expr $no1 * $no2`
        echo "Multi="$mul;;
        4)Div=`expr $no1 / $no2`
        echo "Div="$Div;;
        *)echo "Invalid choice";;
    esac
    echo "Do you want to continue?"
    read i
    if [ $i != "y" ]
    then
        exit
    fi
done