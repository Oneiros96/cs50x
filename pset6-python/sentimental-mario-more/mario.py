from cs50 import get_int
while True:
    amount_of_rows = get_int("Height: ")
    if 1 <= amount_of_rows <= 8:
        break

# If starting with 0 and don't +1 first row would be empty and last one missing
for row in range(1, amount_of_rows + 1):
    print(' ' * (amount_of_rows - row) + '#' * row + '  ' + '#' * row)
