# https://codeforces.com/gym/101889/attachments

def gcd(a, b):
    if a * b == 0:
        return a + b
    elif a == b:
        return a
    return gcd(a%b, b%a)

def phi(n):
    result = 0
    for i in range(1, n):
        if gcd(i, n) == 1:
            result = result + 1
    return result
        
s = list(map(lambda x: x == 'R', input()))
n = len(s)

def calc(m):
    i = 0
    while i < m:
        j= 0
        while j < n//m:
            if not s[j*m+i]:
                break
            j=j+1
        if j == n//m:
            break
        i = i+1
    if i == m:
        return False
    else:
        return True

i = 1
result = 0
while i*i <= n:
    if n%i == 0:
        if calc(i):
            result = result + phi(n//i)
        if i*i < n and i!= 1:
            if calc(n//i):
                result = result + phi(i)
    i=i+1
print(result)
