from sys import stdin

lines = stdin.readlines()
lines = map(lambda line: line.strip(), lines)

def syllable_count(word):
    # Rule 1
    reduced = ""
    for letter in word:
        if letter.isalpha():
            reduced += letter.lower()
    word = reduced
    
    # Rule 2
    isconsonant = []
    i = 0
    while i < len(word):
        letter = word[i]
        if letter not in "qaeiouy":
            isconsonant.append(True)
        else:
            if letter == 'q':
                isconsonant.append(True)
                if i != len(word)-1 and word[i+1] == 'u':
                    i += 1
            elif letter == 'y':
                if i != len(word)-1 and word[i+1] in 'aeiou':
                    isconsonant.append(True)
                else:
                    isconsonant.append(False)
            else:
                isconsonant.append(False)
        i += 1

    # Rule 4
    sylls = 1
    for i in range(len(isconsonant)-1):
        # count of (vowel consonant) patterns [-1 if last letter is not a vowel]
        # = number of consonant runs separated by vowels on *both sides*
        if not isconsonant[i] and isconsonant[i+1]:
            sylls += 1
    if isconsonant[len(isconsonant)-1]:
        sylls -= 1
    # and exceptions
    # 4a
    if word[len(word)-1] == 'e':
        sylls -= 1
        if len(word) >= 3 and word[len(word)-2] == 'l' and isconsonant[len(isconsonant)-3]:
            # double exception, undo
            sylls += 1
    # 4b
    if len(word) >= 2 and word[len(word)-1] == 's' and word[len(word)-2] == 'e':
        sylls -= 1
        if len(isconsonant) >= 4 and isconsonant[len(isconsonant)-3] and isconsonant[len(isconsonant)-4]:
            # double exception, undo
            sylls += 1


    # Rule 3
    return max(1, sylls)
    

def try_haiku(line):
    words = line.split(' ')
    counts = map(syllable_count, words)
    # greedy to see if we can 5-7-5 it
    if sum(counts) == 17:
        running_sum = 0
        index5 = -1
        index12 = -1
        index = 0
        for count in counts:
            running_sum += count
            if running_sum == 5:
                index5 = index
            if running_sum == 12:
                index12 = index
            index += 1

        if index5 != -1 and index12 != -1:
            # we have a haiku! great job
            first_line = ' '.join(words[0:index5+1])
            second_line = ' '.join(words[index5+1:index12+1])
            third_line = ' '.join(words[index12+1:])
            print(first_line)
            print(second_line)
            print(third_line)
            return

    # just return the line unchanged
    print(line)

for line in lines:
    try_haiku(line)
