#!/usr/bin/python
#-*-  coding:utf-8 -*-


import sys


class KmpAlgo (object):
	def __init__ (self, pattern):
		self.m_pattern = pattern
		self.m_piArr = list()
		return
		
	def SetNewPattern (self, pattern):
		self.m_pattern = pattern
		self.m_piArr = list()
		return
		
	def GetPattern (self):
		return self.m_pattern
		
	def __MakePiArr (self, pattern):
		arr = [0]
		n = 0
		
		for i in xrange(1, len(pattern)):
			while n > 0 and pattern[n] != pattern[i]:
				n = arr[n]
			if pattern[n] == pattern[i]:
				n += 1
			arr.append(n)
			
		return arr
		
	def __NaiveMakePiArr (self, strPattern):
		arr = [0]
		
		for i in xrange(2, len (strPattern) + 1):
			subs = strPattern[0 : i]
			#sys.stdout.write(subs + ' - ')
			for j in xrange(len(subs), 1, -1):
				#print ' '*(len(subs)+2), subs[0 : j - 1] , subs[len(subs) - j + 1 : len(subs)]
				if subs[0 : j - 1] == subs[len(subs) - j + 1 : len(subs)]:
					arr.append(j - 1)
					break
				elif j == 2:
					arr.append(0)
		
		return arr
		
	def Search (self, text):
		found = list()
		n = 0
		
		if not self.m_piArr:
			self.m_piArr = self.__MakePiArr(self.m_pattern)
		
		for i in xrange(0, len(text)):
			while n > 0 and self.m_pattern[n] != text[i]:
				n = self.m_piArr[n - 1]
			if self.m_pattern[n] == text[i]:
				n += 1
			if n == len(self.m_pattern):
				found.append(i - len(self.m_pattern) + 1)
				n = self.m_piArr[n - 1]
		
		return found



def main():
	text = 'If an argument xweak is passed, and x is not empty, the weak_ptr object becomes weak part of the owning group weak'
	pattern = 'weak'
	kmpObj = KmpAlgo (pattern)
	res = kmpObj.Search (text)
	
	if res:
		print ("Pattern: %s" % (pattern))
		for i, val in enumerate (res):
			print ("  {0}: position - {1}".format (i, val))
	else:
		print ("Nothing have found")
		
	#print kmpObj._KmpAlgo__NaiveMakePiArr('ababababca')
	#print kmpObj._KmpAlgo__MakePiArr('ababababca')
		
	return 0



if __name__ == '__main__':
	main ()
else:
	print "Importing like a module: {0}".format(__name__)
