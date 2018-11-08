import os 
import matplotlib.pyplot as plt

print(os.listdir())

numWords = 0
maxLen = 0
maxWord = 'maxWord'
length = 0

output = open("output.txt", "w")

with open('words.txt') as f:
    for line in f:
        numWords = numWords + 1
        if(len(line) > maxLen):
            maxLen = len(line) - 1
            maxWord = line
    print('Total number of words: {} \n and maxWord: {} is length: {}'.format(numWords, maxWord, maxLen))
    output.write('Total number of words: {} \n and maxWord: {} is length: {}'.format(numWords, maxWord, maxLen))


#create dictionary to keep track of frequency of words at different sizes, up to 22
wordFreq = {}
for i in range(maxLen):
    wordFreq[i+1] = 0

#print(wordFreq)

#iterate through words again, counting frequency
with open('words.txt') as f:
    for line in f:
        length = len(line) - 1
        wordFreq[length] = wordFreq[length] + 1
        #print(length)
    
print('\nThe amount of words of length: {}'.format(wordFreq))
output.write('\nThe amount of words of length:\n{}'.format(wordFreq))

x = []
y = []
for key in wordFreq:
    x.append(key)
    y.append(wordFreq[key])
print('x: ', x, '\ny: ', y)

plt.plot(x,y)
plt.xlabel('Words')
plt.ylabel('Frequency')
plt.savefig('wordsDist')
plt.show()