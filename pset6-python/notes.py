# python 3
# Commentarys are made with # and should be full sentences.
y = 12
z = 'hi'
if y < 43 or z == 'hello':
    # insert code
elif not y < 43:
    # insert code
else:
    # insert code

#tenary operators
letters_only = True if input().isalpha() else False
# Declares letters_only as a bool wich is set true, if 'userinput'.isalpha(only alphabetic charecters) is true.

# while loops
counter = 0
while counter < 100:
    print(counter)
    counter += 1
# Prints the numbers from 0 to 99 in seperate lines

# for loops
for x in range(100):
    print(x)
# prints evry number
for i in range(0, 100, 2):
    print(x)
# skips evry sekond number

# Arrays in C are lists in python, which are not fixed in size
num = []
# empty list
num = [1, 2, 3, 4]
num.append(5)
# inserst 5 at the end of the list
num.insert(0, 6)
# inserts 6 at the 0th position of the list
nums = [x for x in range(100)]
# list from 0 to 99
num = [1, 2, 3, 4]
num[len(num):] = [5]
# also adds 5 at the end of num. len() calculates the length of a list

# tuples
presidents = [
    ('George Washington', 1789),
    ('John Adams', 1797),
    ('Thomas Jefferson', 1801),
    ('James Madison', 1809)
]
# creates a list oft tuples/linked date that is unlikely to chance
for prez, year in presidents:
    print('In {1}, {0} took office'.format(prez, year))
# Prints for evry tuple in presidents.-> 'In {1 element of tuple}, {0 element of tuple} took...'

# Dictionaries - close to a hash table. Can specify list indices with words ot phrases. Not limited to ints like in c
# while lists are made with [] dictonaries uses {}
pizza = {
    "cheese": 9,
    "pepperoni": 10,
    "vegetable": 11,
    "buffalo chicken": 12
}
# cheese would be the key 8 the assoziated value
pizza['cheese'] = 8
# key cheese now associated with 8
pizza['bacon'] = 14
# adds new key 'bacon'
if pizza['vegetables'] < 12:
    # insert code
for pie in pizza:
    # for evry element in pizza. pie variable like i
    print(pie)
    #prints the key's (cheese, pepperoni etc.)
for pie, price in pizza.items():
    print(price)
    #behaves like a list with the .items(). NOT GARANTEED THAT IT KEEPS THE ORDER
for pie, price in pizza.items():
    print('A whole {} pizza costs ${}'.format(pie, price))
    print('A whole ' + pie + ' pizza costs $' + str(price))
    #behave both the same way

# Functions
def square(x):
    return x * x
    return x ** 2
    # x ** 2 == x²

# Objects