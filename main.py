"""
	Module Usage :
	1. Random module
	2. Math Module (floor)
"""
import random
from math import floor

"""
	Data Structure Usage:
	Polinom data structure
	=> Methods :
		1. generateRandom
		2. getDerajat
		3. setDerajat
		4. getKoefAt
		5. setKoefAt
		6. show -> to show polinom in string / output stream
		7. resetPolinom -> to reset all coeficient to the 0
"""
class Polinom:
	def __init__(self, n):
		self.n = n
		self.koef = self.generateRandom(n)

	def generateRandom(self,n):
		s = []
		for i in range(n+1):
			rand = int(random.random() * 10) + 1
			if random.random() * 10 < 5:
				rand *= -1
			s.append(rand)
		return s

	def panjangPolinom(self):
		return len(self.koef)

	def getKoefAt(self,index):
		return self.koef[index]

	def setKoefAt(self,index,val):
		self.koef[index] = val

	def getDerajat(self):
		return self.n

	def setDerajat(self,n):
		self.n = n

	def show(self):
		for i in range(len(self.koef)):
			if i == 0 : print(self.koef[i], end="")
			elif self.koef[i] > 0:
				if i == 1 : print("+",end="");print(self.koef[i], end="x")
				else :
					print("+",end="")
					print(self.koef[i],end="")
					print(f"x^{i}",end="")
			elif self.koef[i] < 0:
				if i == 1 : print(self.koef[i], end="x")
				else :
					print(self.koef[i],end="")
					print(f"x^{i}",end="")

		print()

	def resetPolinom(self):
		for i in range(len(self.koef)):
			self.koef[i] = 0

"""
	The polynom multiplier function using brute-force algorithm
	Complexity : O(n^2)
"""
def multiply_brute(p1,p2):
	p3 = Polinom(p1.getDerajat() * 2)
	p3.resetPolinom()
	for i in range(p1.getDerajat() + 1):
		for j in range(p2.getDerajat() + 1):
			p3.setKoefAt(i+j,p3.getKoefAt(i+j) + (p1.getKoefAt(i) * p2.getKoefAt(j)))
	return p3

"""
	The polynom multiplier function using divide and conquer strategy
	Complexity : O(n^log3)
"""
def multiply_div(p1,p2):
	if p1.getDerajat() < 2 : 
		return multiply_brute(p1,p2)
	# print("Start")
	# print("P1:",end="");p1.show()
	# print("P2:",end="");p2.show()
	
	a0,a1 = getPartition(p1)
	b0,b1 = getPartition(p2)

	# print("A0:",end="");a0.show()
	# print("A1:",end="");a1.show()
	# print("B0:",end="");b0.show()
	# print("B1:",end="");b1.show()


	x1 = addPolinom(a0,a1); x2 = addPolinom(b0,b1);

	y = multiply_div(x1,x2)
	# print("Done Y:")
	# y.show()
	n = getPembagiDerajat(p1)
	# print("N:",n)
	z = multiply_div(a1,b1)
	# print("Done Z:")
	# z.show()
	u = multiply_div(a0,b0)
	# print("Done U:")
	# u.show()
	mid = subtractPolinom(subtractPolinom(y,u),z)
	# print("Done Mid:")
	# mid.show()
	mid = naikDerajat(mid,n)

	z = naikDerajat(z,n*2)

	return addPolinom(addPolinom(u,mid),z)

# Tested
"""
	Subtracting Polynom Methods
"""
def subtractPolinom(p1,p2):
	# Notes : Have to have same range
	maxDerajat = p1.getDerajat() if p1.getDerajat() >= p2.getDerajat() else p2.getDerajat()
	p3 = Polinom(maxDerajat)
	p3.resetPolinom()

	count = 0
	while (count < p1.panjangPolinom() and count < p2.panjangPolinom()):
		p3.setKoefAt(count,p1.getKoefAt(count) - p2.getKoefAt(count))
		count+=1
	while (count < p1.panjangPolinom()):
		p3.setKoefAt(count,p1.getKoefAt(count))
		count+=1
	while(count < p2.panjangPolinom()):
		p3.setKoefAt(count, p2.getKoefAt(count) * -1)
	return p3

# Tested
"""
	Adding Polynom Methods
"""
def addPolinom(p1,p2):
	# Notes : Have to have same range
	maxDerajat = p1.getDerajat() if p1.getDerajat() >= p2.getDerajat() else p2.getDerajat()
	p3 = Polinom(maxDerajat)
	p3.resetPolinom()

	count = 0
	while (count < p1.panjangPolinom() and count < p2.panjangPolinom()):
		p3.setKoefAt(count,p1.getKoefAt(count) + p2.getKoefAt(count))
		count+=1
	while (count < p1.panjangPolinom()):
		p3.setKoefAt(count,p1.getKoefAt(count))
		count+=1
	while(count < p2.panjangPolinom()):
		p3.setKoefAt(count, p2.getKoefAt(count))
		count+=1
	return p3
	
"""
	To increase polynom degree
	Illustration:
	naikderajat(p,3) => (p) * x^3
"""
def naikDerajat(p,n):
	p_after = Polinom(p.getDerajat() + n)
	p_after.resetPolinom()

	for i in range(p.getDerajat()+1):
		p_after.setKoefAt(i+n,p.getKoefAt(i))

	return p_after

"""
	Return the Floor for the divider part in the algorithm
"""
def getPembagiDerajat(p):
	return p.getDerajat() // 2

def getDerajatPartition(p):
	derajat = p.getDerajat()
	left = (derajat // 2) - 1
	right = derajat - (derajat // 2)

	return left,right

"""
	Methods for partitioning for the divide and conquer strategy
"""
def getPartition(p):
	# print("Partioning")
	left, right = getDerajatPartition(p)
	p1 = Polinom(left)
	p2 = Polinom(right)
	for i in range(p.panjangPolinom()):
		if i <= left : 
			# print("Left:",end="")
			# print(i)
			p1.setKoefAt(i,p.getKoefAt(i))
		else :
			# print("Right:",end="")
			if (p.panjangPolinom() % 2) != 0:
				# print(i-right)
				p2.setKoefAt(i-right,p.getKoefAt(i))
			else:
				# print(i-right+1)
				p2.setKoefAt(i-right+1,p.getKoefAt(i))

	return p1,p2  # return sebagai vector<Polinom> saja

if __name__ == '__main__':
	p1 = Polinom(10)
	p2 = Polinom(10)
	print("P1: ",end="")
	p1.show()
	print()
	print("P2: ",end="")
	p2.show()
	print()
	# p5 = addPolinom(p1,p2)
	# p5.show()

	# p6 = subtractPolinom(p1,p2)
	# p6.show()



	p3 = multiply_div(p1,p2)
	print("Divide-Conquer: ",end="")
	p3.show()
	print()
	p4 = multiply_brute(p1,p2)
	print("Brute Force: ",end="")
	p4.show()
	print()



