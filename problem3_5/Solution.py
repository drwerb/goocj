t = int(raw_input())
for i in xrange(1, t + 1):
    m, n = [int(s) for s in raw_input().split(" ")]
    a = [int(d) for d in raw_input().split(" ")]

    c1 = a[0]
    c2 = 0

    firstDiffIdx = 0

    for j in xrange(1, n):
        if (a[j] != c1):
            c2 = a[j]
            firstDiffIdx = j
            break

    gcd = min(c1, c2)
    c1 = max(c1, c2)
    c2 = gcd

    while (c2 != 0):
        gcd = c2
        c2 = c1 % gcd
        c1 = gcd

    alphabet = []
    aDict = {}
    firstGcd = gcd

    gcd = a[0] / firstGcd
    aDict[gcd] = 1
    alphabet.append(gcd)

    gcd = a[firstDiffIdx - 1] / firstGcd
    for j in xrange(firstDiffIdx - 1, n):
        gcd = a[j] / gcd
        if not (gcd in aDict.keys()):
            aDict[gcd] = 1
            alphabet.append(gcd)

    alphabet.sort()

    gcd = a[firstDiffIdx - 1] / firstGcd
    phrase = ""

    for j in xrange(firstDiffIdx - 1, n):
        gcd = a[j] / gcd
        phrase = phrase + chr(ord('A') + alphabet.index(gcd))

    gcd = firstGcd
    for j in reversed(xrange(0, firstDiffIdx)):
        gcd = a[j] / gcd
        phrase = chr(ord('A') + alphabet.index(gcd)) + phrase

    print "Case #{}: {}".format(i, phrase)
