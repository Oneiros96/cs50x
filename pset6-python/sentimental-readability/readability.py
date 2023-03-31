from cs50 import get_string

text = get_string('Text: ')

letters = 0
# Because words are detectet by ' ' there will be one more word then countet
words = 1
sentences = 0
for char in text:
    # Checks for alphabetic charecters
    if char.isalpha():
        letters += 1
    # Checks for new words
    elif char == ' ':
        words += 1
    # Checks for sentences
    elif char == '!' or char == '.' or char == '?':
        sentences += 1
# Coleman-Liau index
grade = round(0.0588 * (letters / words * 100) - 0.296 * (sentences / words * 100) - 15.8)

if grade < 1:
    print('Before Grade 1')
elif grade > 16:
    print('Grade 16+')
else:
    print(f'Grade {grade}')
