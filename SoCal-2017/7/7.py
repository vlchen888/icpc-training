from sys import stdin

lines = stdin.readlines()
lines = map(lambda line: line.split(','), lines)

[H, W] = map(int, lines[0])
H = H*1.0
W = W*1.0
lines = lines[1:]

def checkleft(bx, leftcoords, rightcoords):
    balldiff = max(0, W/2 - bx)
    diffs = []
    for counter in range(11):
        cx = rightcoords[counter*2]
        if cx >= W/2:
            diffs.append(0)
        else:
            diffs.append(W/2 - cx)
    diffs.sort()
    ret = []
    for counter in range(11):
        cx = leftcoords[counter*2]
        diff = max(0, W/2 - cx)
        if cx > 0 and diff < diffs[1] and diff < balldiff:
            ret.append(counter+1)

    return ret

def checkright(bx, leftcoords, rightcoords):
    balldiff = max(0, bx + W/2)
    diffs = []
    for counter in range(11):
        cx = leftcoords[counter*2]
        if cx <= -W/2:
            diffs.append(0)
        else:
            diffs.append(cx + W/2)
    diffs.sort()
    ret = []
    for counter in range(11):
        cx = rightcoords[counter*2]
        diff = max(0, cx + W/2)
        if cx < 0 and diff < diffs[1] and diff < balldiff:
            ret.append(counter+1)

    return ret

counter = 0
while counter < len(lines):
    [timestamp, bx, by] = lines[counter]
    bx = int(bx)
    by = int(by)
    leftcoords = map(int, lines[counter+1])
    rightcoords = map(int, lines[counter+2])
    
    leftoff = checkleft(bx, leftcoords, rightcoords)
    rightoff = checkright(bx, leftcoords, rightcoords)
    
    if len(leftoff) != 0 or len(rightoff) != 0:
        ret = timestamp
        if len(leftoff) != 0:
            ret += " Left " + " ".join(map(str, leftoff))
        if len(rightoff) != 0:
            ret += " Right " + " ".join(map(str, rightoff))
        print(ret)
    counter += 3
