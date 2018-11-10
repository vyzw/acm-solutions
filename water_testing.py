# https://codeforces.com/gym/101873/problem/B

n = int(input())
xs = list()
ys = list()

for i in range(n) :
	x, y = map(int, input().split())
	xs.append(x)
	ys.append(y)
	
area = xs[-1] * ys[0] - xs[0] * ys[-1]
for i in range(1, n) :
	area += xs[i-1] * ys[i] - xs[i] * ys[i-1]

area = abs(area) / 2

# print(area)

def gcd(a, b) :
	if b == 0 :
		return a
	return gcd(b, a % b)
	
b = gcd(abs(xs[-1] - xs[0]), abs(ys[-1] - ys[0]))

for i in range(1, n) :
	b += gcd(abs(xs[i-1] - xs[i]), abs(ys[i-1] - ys[i]))

area += 1
area -= (b / 2)

print(int(area))