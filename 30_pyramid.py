# Write a program to display the following pyramid. The number of lines in the pyramid should not be hard-coded. 
# It should be obtained from the user.The pyramid should appear as close to the center of the screen as possible. 


import os

#get terminal size
rows,columns = os.popen('stty size','r').read().split()
r = int(rows)
c = int(columns)


#Input number of Rows
n = int(input("Enter number of Rows"))

#calculate upper and lower margin
upper_margin = int((r-n)/2)
lower_margin = r - n - upper_margin

#Print upper Margin
for _ in range(upper_margin):
    print()

#print pattern

for i in range(n):
    #leading spaces
    for _ in range(int(c/2) - int(n/2)):
        print(" ",end="")
    #spaces before stars
    for _ in range(n-i-1):
        print(" ",end="")
    #printing starts
    for _ in range(2*i+1):
        print("*",end="")
    print()

# Print lower margin
for _ in range(lower_margin):
    print()